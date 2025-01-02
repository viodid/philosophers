/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:19:45 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/02 12:53:40 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void		philo_process(t_philosopher *philo);
static sem_t	*open_semaphore(const t_args *args, const char *sem_name);
static void		close_semaphore(const char *sem_name);

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
	t_philosopher	*philo;

	philo = header;
	if (philo->args->no_philo == 0)
		return;
	sem = open_semaphore(philo->args, SEM_FORKS);

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

	pids = (pid_t *) malloc(sizeof(int) * philo->args->no_philo);
	if (!pids)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	pids[0] = fork();
	i = 1;
	while (i < philo->args->no_philo)
	{
		if (pids[i - 1] != 0)
			pids[i] = fork();
		i++;
	}
	i = 0;
	while (i < philo->args->no_philo)
	{
		if (pids[i] != 0)
			waitpid(pids[i], NULL, 0);
		else
		{
			free(pids);
			philo_process(philo);
			return ;
		}
		i++;
	}
	free(pids);
	printf("parent pid: %d\n", getpid());
	close_semaphore(SEM_FORKS);
}

static void	philo_process(t_philosopher *philo)
{
	// sem_t	*sem;

	// sem = open_semaphore(philo->args, SEM_FORKS);

	usleep(1000 * 1000);
	printf("child pid: %d\n", getpid());
	printf("args: %d\n", philo->args->no_philo);
}

static sem_t	*open_semaphore(const t_args *args, const char *sem_name)
{
	sem_t	*sem;

	sem = sem_open(sem_name, O_CREAT, O_RDWR, args->no_philo);
	if (sem == SEM_FAILED)
	{
		perror("semaphore error"); // remove forbidden func
		exit(EXIT_FAILURE);
	}
	return (sem);
}

static void		close_semaphore(const char *sem_name)
{
	int	ret;

	ret = sem_unlink(sem_name);
	if (ret == -1)
	{
		perror("sem unlink"); // rm forbidden func
		exit(EXIT_FAILURE);
	}
}

