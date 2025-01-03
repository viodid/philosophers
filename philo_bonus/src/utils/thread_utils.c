/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:44 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/03 11:42:18 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

void	create_thread(t_philosopher *philo)
{
	if (pthread_create(&philo->thread, NULL, watcher_routine, (void *)philo))
	{
		perror("pthread_create"); // forbidden func
		exit(EXIT_FAILURE);
	}
}

void	join_thread(t_philosopher *philo)
{
	if (pthread_join(philo->thread, NULL))
	{
		perror("pthread_join");
		exit(EXIT_FAILURE); // forbidden func
	}
}