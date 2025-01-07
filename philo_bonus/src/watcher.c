/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:55:01 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/07 09:07:29 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static long		compute_time_ms(t_timeval upper_val, t_timeval lower_val);

void	*watcher_routine(void *data)
{
	t_philosopher	*philo;
	t_timeval		curr_time;
	long			time;
	sem_t			*sem_die;

	philo = (t_philosopher *)data;
	sem_die = open_semaphore(SEM_DIE, 1);
	usleep(1000 * 10);
	while (philo->no_meals != philo->args->total_no_meals)
	{
		gettimeofday(&curr_time, NULL);
		time = compute_time_ms(curr_time, philo->timestamp);
		if (time > (philo->args->time_to_die * 1000))
		{
			printf("time: %ld\n", time);
			state_printer(philo, DIED);
			wait_semaphore(sem_die);
			printf("after die\n");
			break;
		}
		usleep(100);
	}
	close_semaphore(sem_die);
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
