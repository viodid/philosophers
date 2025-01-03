/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:55:01 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/03 11:52:49 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static long		compute_time_ms(t_timeval upper_val, t_timeval lower_val);

void	*watcher_routine(void *data)
{
	t_philosopher	*philo;
	t_timeval		curr_time;
	long			time;

	philo = (t_philosopher *)data;
	while (philo->no_meals != philo->args->total_no_meals)
	{
		gettimeofday(&curr_time, NULL);
		time = compute_time_ms(curr_time, philo->timestamp);

		printf("time: %ld - time_to_die: %u\n", time, philo->args->time_to_die * 1000);
		// BUGFIX: do not compare agains time_to_die
		if (time > (philo->args->time_to_die * 1000))
		{
//			pthread_mutex_lock(&philo->m_die); TODO: should be a semaphore
			state_printer(philo, DIED);
			return (NULL);
		}
		usleep(100); // TODO: set to 10
	}
	return (NULL);
}

static long	compute_time_ms(const t_timeval upper_val, const t_timeval lower_val)
{
	long	sec;
	long	micros;

	sec = upper_val.tv_sec - lower_val.tv_sec;
	micros = upper_val.tv_usec - lower_val.tv_usec;
	return ((sec * 1000 * 1000) + micros);
}
