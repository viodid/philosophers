/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:23:54 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/03 13:19:55 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

static t_philosopher	*select_philo(t_philosopher *head, const uint process_no);

void	handle_threads(pid_t *pids, t_philosopher *head, uint process_no, sem_t *sem)
{
	t_philosopher	*philo;
	pthread_t		thread_watcher;

	free(pids);
	close_semaphore(sem);
	philo = select_philo(head, process_no);
	create_thread(&philo->thread, philo_thread, (void *)philo);
	create_thread(&thread_watcher, watcher_routine, (void *)philo);
	detach_thread(philo->thread);
	join_thread(thread_watcher);
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
