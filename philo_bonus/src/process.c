/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:19:45 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/31 12:43:51 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philosophers(t_args *args) {
	int *pids;
	uint i;

	if (args->no_philo == 0)
		return;
	// create a semaphore and initialize it with no_philos.
	// allocate an array of pids
	// everytime a child process is created, store its pid into pids.
	// to keep things simple, don't nest child processes.
	// if process is a child, execute philo routine and watcher
	// in the main process, wait for all the children to change state
	pids = (int *) malloc(sizeof(int) * args->no_philo);
	i = 1;
}
