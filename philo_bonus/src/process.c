/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:19:45 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/31 13:12:06 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	philo(void)
{
	printf("child pid: %d\n", getpid());
}

void	philosophers(t_args *args) {
	pid_t *pids;
	uint i;

	if (args->no_philo == 0)
		return;
	// create a semaphore and initialize it with no_philos.
	// allocate an array of pids
	// everytime a child process is created, store its pid into pids.
	// to keep things simple, don't nest child processes.
	// if process is a child, execute philo routine and watcher
	// in the main process, wait for all the children to change state
	pids = (pid_t *) malloc(sizeof(int) * args->no_philo);
	pids[0] = fork();
	i = 1;
	while (i < args->no_philo)
	{
		if (pids[i - 1] != 0)
			pids[i] = fork();
		i++;
	}
	i = 0;
	while (i < args->no_philo)
	{
		if (pids[i] != 0)
			waitpid(pids[i], NULL, 0);
		else
		{
			free(pids);
			philo();
			return ;
		}
		i++;
	}
	free(pids);
	printf("parent pid: %d\n", getpid());
}
