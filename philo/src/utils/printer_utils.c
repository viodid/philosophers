/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:01:23 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/26 13:13:42 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static char	*map_state(t_states state);

void	philo_printer(t_philosopher *philo, t_states state)
{
	t_timeval	curr_time;
	long		sec;
	long		ms;

	gettimeofday(&curr_time, NULL);
	sec = curr_time.tv_sec - philo->timestamp.tv_sec;
	ms = (curr_time.tv_usec - philo->timestamp.tv_usec) / 1000;
	printf("%ld:%ld %d %s\n", sec, ms, philo->thread_no, map_state(state));
}

static char	*map_state(t_states state)
{
	if (state == FORK)
		return ("has taken a fork");
	else if (state == EAT)
		return ("is eating");
	else if (state == SLEEP)
		return ("is sleeping");
	else if (state == THINK)
		return ("is thinking");
	else if (state == DIED)
		return ("died");
	else
		return (NULL);
}
