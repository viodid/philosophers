/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:18:57 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/26 10:42:29 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static u_int8_t	check_finished_meal(t_philosopher *philo);

u_int8_t	check_starvation(t_philosopher *philo, t_timeval curr_time)
{
	if (check_finished_meal(philo))
		return (FALSE);
	if ((curr_time.tv_usec - philo->timestamp.tv_usec) > (philo->args->time_to_die * 1000))
	{
		printf("philo no: %d has died\n", philo->thread_no);
		return (TRUE);
	}
	return (FALSE);
}

static u_int8_t	check_finished_meal(t_philosopher *philo)
{
	printf("philo no: %d has eaten: %d times\n", philo->thread_no, philo->no_meals);
	if (philo->no_meals == philo->args->total_no_meals)
		return (TRUE);
	return (FALSE);
}

void	*watcher_routine(void *data)
{
	t_philosopher	*philo;
	t_philosopher	*head;
	t_timeval		curr_time;
	uint			finished_philos;

	philo = (t_philosopher *)data;
	head = philo;
	finished_philos = 0;
	while (finished_philos < head->args->no_philo)
	{
		gettimeofday(&curr_time, NULL);
		while (philo->next != head)
		{
			if (check_starvation(philo, curr_time))
				return (NULL);
			if (check_finished_meal(philo))
				finished_philos++;
			philo = philo->next;
		}
		if (check_starvation(philo, curr_time))
			return (NULL);
		if (check_finished_meal(philo))
			finished_philos++;
		philo = philo->next;
		usleep(500);
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
		printf("thread no: %d - timestamp: %ld - %ld\n", philo->thread_no, philo->timestamp.tv_sec, philo->timestamp.tv_usec);
		usleep(philo->args->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&philo->next->mutex);
		philo->no_meals++;
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
}
