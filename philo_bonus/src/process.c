/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:19:45 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/02 14:58:44 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void		philo_process(t_philosopher *philo);
static t_philosopher	*select_philo(t_philosopher *head, uint i);

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

	int wait_ret = sem_wait(sem);
	if (wait_ret == -1)
		perror("sem_wait");
	else
		printf("sem wait: %d\n", wait_ret);
	int post_ret = sem_post(sem);
	if (post_ret == -1)
		perror("sem_post");
	else
		printf("sem post: %d\n", post_ret);

	pids = (pid_t *) malloc(sizeof(int) * header->args->no_philo);
	if (!pids)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	pids[0] = fork();
	if (pids[0] == 0)
	{
		free(pids);
		close_semaphore(sem);
		philo_process(select_philo(header, 1));
		return ;
	}
	i = 1;
	while (i < header->args->no_philo)
	{
		if (pids[i - 1] != 0)
			pids[i] = fork();
		if (pids[i] == 0)
		{
			free(pids);
			close_semaphore(sem);
			philo_process(select_philo(header, i + 1));
			return ;
		}
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

static void	philo_process(t_philosopher *philo)
{
	sem_t	*sem;

	printf("child pid: %d\n", getpid()); // rm
	printf("process_no: %d\n", philo->process_no);

	sem = open_semaphore(philo->args, SEM_FORKS);
	if (philo->process_no % 2 == 0)
		usleep(500);
	gettimeofday(&philo->timestamp, NULL);
	// TODO: watcher thread routine

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
}

static t_philosopher	*select_philo(t_philosopher *head, const uint i)
{
	t_philosopher	*philo;

	philo = head;
	while (philo)
	{
		if (philo->process_no == i)
			return (philo);
		philo = philo->next;
	}
	return (philo);
}
