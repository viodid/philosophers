/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:55:13 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/07 12:54:46 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

void	free_philosophers(t_philosopher *philo)
{
	t_philosopher	*next;

	if (!philo)
		return ;
	while (philo)
	{
		next = philo->next;
		free(philo->custom_sem_name);
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
	output[4] = (char)(48 + (process_no / 100));
	output[5] = (char)(48 + ((process_no / 10) % 10));
	output[6] = (char)(48 + (process_no % 10));
	output[7] = '\0';
	return (output);
}

void	deallocate_semaphores(t_philosopher *head)
{
	t_philosopher	*philo;

	philo = head;
	unlink_semaphore(SEM_FORKS);
	while (philo)
	{
		unlink_semaphore(philo->custom_sem_name);
		philo = philo->next;
	}
}

t_philosopher	*select_philo(t_philosopher *head, const uint process_no)
{
	t_philosopher	*philo;

	philo = head;
	while (philo)
	{
		if (philo->process_no == process_no)
			return (philo);
		philo = philo->next;
	}
	return (philo);
}
