/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:18:57 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/30 17:56:12 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*philo_routine(void *data);
static void	detach_threads(t_philosopher *head);

void	philosophers(t_philosopher *head)
{
	uint			i;
	t_philosopher	*philo;
	pthread_t		watcher;

	philo = head;
	i = 0;
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
	detach_threads(head);
	pthread_join(watcher, NULL);
}

// Every odd thread should wait to take the forks inside its thread execution
static void	*philo_routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	philo->no_meals = 0;
	if (philo->thread_no % 2 == 0)
		usleep(5000);
	gettimeofday(&philo->timestamp, NULL);
	while (philo->no_meals != philo->args->total_no_meals)
	{
		pthread_mutex_lock(&philo->m_fork);
		state_printer(philo, FORK);
		pthread_mutex_lock(&philo->next->m_fork);
		pthread_mutex_lock(&philo->m_die);
		state_printer(philo, FORK);
		gettimeofday(&philo->timestamp, NULL);
		state_printer(philo, EAT);
		usleep(philo->args->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->m_fork);
		pthread_mutex_unlock(&philo->next->m_fork);
		pthread_mutex_unlock(&philo->m_die);
		philo->no_meals++;
		state_printer(philo, SLEEP);
		usleep(philo->args->time_to_sleep * 1000);
		state_printer(philo, THINK);
	}
	return (NULL);
}

static void	detach_threads(t_philosopher *head)
{
	t_philosopher	*philo;

	philo = head;
	while (philo->next != head)
	{
		pthread_detach(philo->thread);
		philo = philo->next;
	}
	pthread_detach(philo->thread);
}
