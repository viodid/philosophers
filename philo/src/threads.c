/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:18:57 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/24 19:31:19 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *philo)
{
	return (NULL);
}

static void	create_threads(t_philosopher *philo, uint philo_no)
{
	if (philo_no % 2 == 1)
		usleep(5000);
	pthread_create(&philo->thread, NULL, routine, (void *)philo);
}

void	philosophers(t_philosopher *head)
{
	uint			i;
	t_philosopher	*philo;

	philo = head;
	i = 0;
	while (philo->next != head)
	{
		create_threads(philo, i);
		philo = philo->next;
		i++;
	}
	create_threads(philo, i);
}
