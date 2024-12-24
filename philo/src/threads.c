/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:18:57 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/24 19:36:50 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*watcher_routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	return (NULL);
}

void	*philo_routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	return (NULL);
}

static void	create_thread(t_philosopher *philo, uint philo_no)
{
	if (philo_no % 2 == 1)
		usleep(5000);
	pthread_create(&philo->thread, NULL, philo_routine, (void *)philo);
}

void	philosophers(t_philosopher *head)
{
	uint			i;
	t_philosopher	*philo;
	pthread_t		watcher;

	philo = head;
	i = 0;
	while (philo->next != head)
	{
		create_thread(philo, i);
		philo = philo->next;
		i++;
	}
	create_thread(philo, i);
	pthread_create(&watcher, NULL, watcher_routine, (void *)head);
}
