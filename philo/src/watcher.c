/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:55:01 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/30 16:45:29 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static uint	check_all_finished_meals(t_philosopher *philo);
static u_int8_t	check_starvation(t_philosopher *philo);
static long	compute_time_ms(t_timeval upper_val, t_timeval lower_val);

void	*watcher_routine(void *data)
{
	t_philosopher	*philo;
	t_philosopher	*head;

	philo = (t_philosopher *)data;
	head = philo;
	while (check_all_finished_meals(head) < head->args->no_philo)
	{
		while (philo->next != head)
		{
			if (check_starvation(philo))
				return (NULL);
			philo = philo->next;
		}
		if (check_starvation(philo))
			return (NULL);
		philo = philo->next;
		usleep(1000 * 2);
	}
	return (NULL);
}

static uint	check_all_finished_meals(t_philosopher *philo)
{
	t_philosopher	*head;
	uint			output;

	head = philo;
	output = 0;
	while (philo->next != head)
	{
		if (philo->no_meals == philo->args->total_no_meals)
			output++;
		philo = philo->next;
	}
	if (philo->no_meals == philo->args->total_no_meals)
		output++;
	return (output);
}

static u_int8_t	check_starvation(t_philosopher *philo)
{
	t_timeval	curr_time;

	if (philo->no_meals == philo->args->total_no_meals)
		return (FALSE);
	gettimeofday(&curr_time, NULL);
	long op = compute_time_ms(curr_time, philo->timestamp);
	if (op > (philo->args->time_to_die * 1000))
	{
		pthread_mutex_lock(&philo->m_die);
		state_printer(philo, DIED);
		return (TRUE);
	}
	return (FALSE);
}

static long	compute_time_ms(t_timeval upper_val, t_timeval lower_val)
{
	long	sec;
	long	micros;

	sec = upper_val.tv_sec - lower_val.tv_sec;
	micros = upper_val.tv_usec - lower_val.tv_usec;
	return ((sec * 1000 * 1000) + micros);
}
