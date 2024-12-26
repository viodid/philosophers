/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:18:57 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/26 13:23:02 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*philo_routine(void *data);
static void	join_threads(t_philosopher *head);

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

// Every odd thread should wait to take the forks inside its thread execution
static void	*philo_routine(void *data)
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
		state_printer(philo, FORK);
		gettimeofday(&philo->timestamp, NULL);
		state_printer(philo, EAT);
		usleep(philo->args->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&philo->next->mutex);
		philo->no_meals++;
		state_printer(philo, SLEEP);
		usleep(philo->args->time_to_sleep * 1000); // sleep
		state_printer(philo, THINK);
	}
//	pthread_mutex_destroy(&philo->mutex);
	return (NULL);
}

static void	join_threads(t_philosopher *head)
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
