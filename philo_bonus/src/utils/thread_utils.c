/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:44 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/06 18:59:48 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

void	create_thread(pthread_t* thread, void *routine, void *payload)
{
	if (pthread_create(thread, NULL, routine, payload))
	{
		perror("pthread_create"); // forbidden func
		exit(EXIT_FAILURE);
	}
}

void	join_thread(const pthread_t thread)
{
	if (pthread_join(thread, NULL))
	{
		perror("pthread_join");
		exit(EXIT_FAILURE); // forbidden func
	}
}

void	detach_thread(const pthread_t thread)
{
	if (pthread_detach(thread))
	{
		perror("pthread_detach"); // FORBIDDEN
		exit(EXIT_FAILURE);
	}
}
