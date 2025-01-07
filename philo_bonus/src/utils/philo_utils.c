/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:55:13 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/07 10:52:37 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

void	free_philosophers(t_philosopher *philo)
{
	t_philosopher	*next;
	if (!philo)
		return ;
	printf("free_philos\n");
	while (philo)
	{
		next = philo->next;
		free(philo);
		philo = next;
	}
}

char	*hash_name(const uint process_no)
{
	char		*output;

	output = (char *)malloc(sizeof(char) * 8);
	output[0] = '/';
	output[1] = 'D';
	output[2] = 'I';
	output[3] = 'E';
	output[4] = (char) (48 + (process_no / 100));
	output[5] = (char) (48 + ((process_no / 10) % 10));
	output[6] = (char) (48 + (process_no % 10));
	output[7] = '\0';
	return (output);
}
