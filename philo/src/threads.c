/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:18:57 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/24 20:12:40 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//void	*watcher_routine(void *data)
//{
//	t_philosopher	*philo;
//
//	philo = (t_philosopher *)data;
//	return (NULL);
//}

// Every odd thread should wait to take the forks inside its thread execution
void	*philo_routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	if (philo->thread_no % 2 == 0)
		usleep(5000);
	printf("thread no: %d\n", philo->thread_no);
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
//	pthread_t		watcher;

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
//	pthread_create(&watcher, NULL, watcher_routine, (void *)head);
	join_threads(head);
}
