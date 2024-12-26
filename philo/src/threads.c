/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:18:57 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/26 12:34:22 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static u_int8_t	check_finished_meal(t_philosopher *philo);

static long	compute_time_ms(t_timeval upper_val, t_timeval lower_val)
{
	long	sec;
	long	micros;

	sec = upper_val.tv_sec - lower_val.tv_sec;
	micros = upper_val.tv_usec - lower_val.tv_usec;
	return ((sec * 1000 * 1000) + micros);
}

u_int8_t	check_starvation(t_philosopher *philo)
{
	t_timeval	curr_time;

	if (check_finished_meal(philo))
		return (FALSE);
	gettimeofday(&curr_time, NULL);
	long op = compute_time_ms(curr_time, philo->timestamp);
	printf("philo no: %d has not eaten since: %ld microseconds\n", philo->thread_no, op);
	if (op > (philo->args->time_to_die * 1000))
	{
		printf("philo no: %d has died\n", philo->thread_no);
		return (TRUE);
	}
	return (FALSE);
}

static u_int8_t	check_finished_meal(t_philosopher *philo)
{
	if (philo->no_meals == philo->args->total_no_meals)
	{
		printf("philo: %d has finished its meals\n", philo->thread_no);
		return (TRUE);
	}
	return (FALSE);
}

static uint	check_all_finished_meals(t_philosopher *philo)
{
	t_philosopher	*head;
	uint			output;

	head = philo;
	output = 0;
	while (philo->next != head)
	{
		if (philo->no_meals == philo->args->total_no_meals)
			output++;
		philo = philo->next;
	}
	if (philo->no_meals == philo->args->total_no_meals)
		output++;
	printf("total no of finished meals: %d\n", output);
	return (output);
}

void	*watcher_routine(void *data)
{
	t_philosopher	*philo;
	t_philosopher	*head;

	philo = (t_philosopher *)data;
	head = philo;
	while (check_all_finished_meals(head) < head->args->no_philo)
	{
		while (philo->next != head)
		{
			printf("philo no: %d has eaten: %d times\n", philo->thread_no, philo->no_meals);
			if (check_starvation(philo))
				return (NULL);
			philo = philo->next;
		}
		printf("philo no: %d has eaten: %d times\n", philo->thread_no, philo->no_meals);
		if (check_starvation(philo))
			return (NULL);
		philo = philo->next;
		usleep(1000 * 1000);
	}
	return (NULL);
}

// Every odd thread should wait to take the forks inside its thread execution
void	*philo_routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	// Count time without eating since the start of the simulation
	gettimeofday(&philo->timestamp, NULL);
	philo->no_meals = 0;
	if (philo->thread_no % 2 == 0)
		usleep(5000); // set to half millisecond in case input arg is 1(500)

	// check total number of meals
	// Lock philo own mutex and next one (eat)
	// Set timestamp
	// Eat (usleep)
	// Unlock mutexes
	// sleep (usleep)
	while (philo->no_meals != philo->args->total_no_meals)
	{
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_lock(&philo->next->mutex);
		gettimeofday(&philo->timestamp, NULL);
		philo->no_meals++;
		printf("thread no: %d - timestamp: %ld - %ld\n", philo->thread_no, philo->timestamp.tv_sec, philo->timestamp.tv_usec);
		usleep(philo->args->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&philo->next->mutex);
		usleep(philo->args->time_to_sleep * 1000);
	}
//	pthread_mutex_destroy(&philo->mutex);
	return (NULL);
}

void	join_threads(t_philosopher *head)
{
	t_philosopher	*philo;

	philo = head;
	while (philo->next != head)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
	}
	pthread_join(philo->thread, NULL);
}

void	philosophers(t_philosopher *head)
{
	uint			i;
	t_philosopher	*philo;
	pthread_t		watcher;

	philo = head;
	i = 0;
	// Wait some microseconds for every thread to take the forks.
	while (philo->next != head)
	{
		usleep(10);
		pthread_create(&philo->thread, NULL, philo_routine, (void *)philo);
		philo = philo->next;
		i++;
	}
	usleep(10);
	pthread_create(&philo->thread, NULL, philo_routine, (void *)philo);
	pthread_create(&watcher, NULL, watcher_routine, (void *)head);
	join_threads(head);
	pthread_join(watcher, NULL);
}
