/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:01:23 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/27 12:48:53 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static char	*map_state(t_states state);

void	state_printer(t_philosopher *philo, t_states state)
{
	t_timeval	curr_time;
	char		*state_str;
//	static long	seconds_base = 0;

	gettimeofday(&curr_time, NULL);
//	seconds_base = curr_time.tv_sec - seconds_base;
	state_str = map_state(state);
	printf("%ld:%ld \t%d %s\n",curr_time.tv_sec ,curr_time.tv_usec, philo->thread_no, state_str);
	free(state_str);
}

static uint	ft_strlen(char *str)
{
	uint	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

static char	*ft_strjoin(char *str1, char *str2)
{
	uint	length;
	uint	i;
	char	*output;

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
		output[i + ft_strlen(str1)] = str2[i];
		i++;
	}
	output[i + ft_strlen(str1)] = '\0';
	return (output);
}

static char	*add_color(char *color, char *str)
{
	char	*join1;
	char	*join2;

	join1 = ft_strjoin(color, str);
	join2 = ft_strjoin(join1, RES);
	free(join1);
	return (join2);
}

static char	*map_state(t_states state)
{
	if (state == FORK)
		return (add_color(GRN_BOLD, "has taken a fork"));
	else if (state == EAT)
		return (add_color(X_BOLD, "is eating"));
	else if (state == SLEEP)
		return (add_color(BLU_BOLD, "is sleeping"));
	else if (state == THINK)
		return (add_color(Y_BOLD, "is thinking"));
	else if (state == DIED)
		return (add_color(RED_BOLD, "died"));
	return (NULL);
}
