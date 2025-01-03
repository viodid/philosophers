/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:19:45 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/03 13:01:25 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

/* create a semaphore and initialize it with `no_philos`.
 * allocate an array of pids
 * everytime a child process is created, store its pid into pids.
 * to keep things simple, don't nest child processes.
 * if process is a child, execute philo routine and watcher.
 * the watcher routine should be executed asynchronously.
 * in the main process, wait for all the children to change state
*/
void	philosophers(t_philosopher *header) {
	pid_t	*pids;
	uint	i;
	sem_t	*sem;

	if (header->args->no_philo == 0)
		return;
	sem = open_semaphore(header->args, SEM_FORKS);
	pids = (pid_t *) malloc(sizeof(int) * header->args->no_philo);
	if (!pids)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	pids[0] = fork();
	if (pids[0] == 0)
		return (handle_threads(pids, header, 1, sem));
	i = 1;
	while (i < header->args->no_philo)
	{
		if (pids[i - 1] != 0)
			pids[i] = fork();
		if (pids[i] == 0)
			return (handle_threads(pids, header, i + 1, sem));
		i++;
	}
	i = 0;
	while (i < header->args->no_philo)
	{
		if (pids[i] != 0)
			if (waitpid(pids[i], NULL, 0) == -1)
				perror("waitpid");
		i++;
	}
	free(pids);
	printf("parent pid: %d\n", getpid());
	close_semaphore(sem);
	unlink_semaphore(SEM_FORKS);
}

void	*philo_thread(void *data)
{
	sem_t	*sem;
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	printf("child pid: %d\n", getpid()); // rm
	printf("process_no: %d\n", philo->process_no);

	sem = open_semaphore(philo->args, SEM_FORKS);
	gettimeofday(&philo->timestamp, NULL);
	while (philo->no_meals != philo->args->total_no_meals)
	{
		wait_semaphore(sem);
		wait_semaphore(sem);
		state_printer(philo, FORK);
		gettimeofday(&philo->timestamp, NULL);
		state_printer(philo, EAT);
		usleep(philo->args->time_to_sleep * 1000);
		post_semaphore(sem);
		post_semaphore(sem);
		philo->no_meals++;
		state_printer(philo, SLEEP);
		usleep(philo->args->time_to_sleep * 1000);
		state_printer(philo, THINK);
	}
	close_semaphore(sem);
	return (NULL);
}
