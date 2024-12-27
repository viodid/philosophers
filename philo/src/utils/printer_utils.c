/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:01:23 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/27 11:46:29 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static char	*map_state(t_states state);

void	state_printer(t_philosopher *philo, t_states state)
{
	t_timeval	curr_time;
//	static long	seconds_base = 0;

	gettimeofday(&curr_time, NULL);
//	seconds_base = curr_time.tv_sec - seconds_base;
	printf("%ld:%ld \t%d %s\n",curr_time.tv_sec ,curr_time.tv_usec, philo->thread_no, map_state(state));
}

static uint	ft_strlen(char *str)
{
	uint	i;

	i = 0;
	while (*str++)
		i++;
	return(i);
}

static char	*ft_strjoin(char *str1, char *str2) {
	uint length;
	uint i;
	char *output;

	length = ft_strlen(str1) + ft_strlen(str2) + 1;
	output = (char *) malloc(sizeof(char) * length);
	if (!output)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < ft_strlen(str1))
	{
		output[i] = str1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(str2))
	{
		output[i + ft_strlen(str1)] = str1[i];
		i++;
	}
	output[i + ft_strlen(str1)] = '\0';
	return (output);
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
