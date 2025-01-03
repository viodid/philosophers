/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:23:54 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/03 12:25:18 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

static t_philosopher	*select_philo(t_philosopher *head, const uint process_no);

void	free_pids_create_thread(pid_t *pids, t_philosopher *head, uint process_no, sem_t *sem)
{
	free(pids);
	close_semaphore(sem);
	create_thread(select_philo(head, process_no));
}

static t_philosopher	*select_philo(t_philosopher *head, const uint process_no)
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
