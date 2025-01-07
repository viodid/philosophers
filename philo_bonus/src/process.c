/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:19:45 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/07 12:54:33 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	close_processes(const pid_t *pids, uint no_processes);
static void	handle_threads(pid_t *pids, t_philosopher *head, uint process_no);
static void	philo_thread_routine(sem_t *sem_fork, sem_t *sem_die,
				t_philosopher *philo);
static void	*philo_thread(void *data);

/* create a semaphore and initialize it with `no_philos`.
 * allocate an array of pids
 * everytime a child process is created, store its pid into pids.
 * to keep things simple, don't nest child processes.
 * if process is a child, execute philo routine and watcher.
 * the watcher routine should be executed asynchronously.
 * in the main process, wait for all the children to change state
*/
void	philosophers(t_philosopher *header)
{
	pid_t	*pids;
	uint	i;

	if (header->args->no_philo == 0)
		return ;
	pids = (pid_t *) malloc(sizeof(int) * header->args->no_philo);
	if (!pids)
		exit(EXIT_FAILURE);
	pids[0] = fork();
	if (pids[0] == 0)
		return (handle_threads(pids, header, 1));
	i = 1;
	while (i < header->args->no_philo)
	{
		if (pids[i - 1] != 0)
			pids[i] = fork();
		if (pids[i] == 0)
			return (handle_threads(pids, header, i + 1));
		i++;
	}
	close_processes(pids, header->args->no_philo);
	free(pids);
	deallocate_semaphores(header);
}

/*
 * This function block execution until one of the process ids in pids has
 * already finished. Then, it kills the remaining processes ids in pids.
*/
static void	close_processes(const pid_t *pids, const uint no_processes)
{
	uint		i;
	pid_t		dealloc_process;

	i = 0;
	dealloc_process = waitpid(-1, NULL, 0);
	while (i < no_processes)
	{
		if (pids[i] != dealloc_process)
			kill(pids[i], SIGKILL);
		i++;
	}
}

static void	handle_threads(pid_t *pids, t_philosopher *head,
		const uint process_no)
{
	t_philosopher	*philo;
	pthread_t		thread_philo;
	pthread_t		thread_watcher;

	philo = select_philo(head, process_no);
	if (philo->process_no % 2 == 0)
		usleep(500);
	create_thread(&thread_philo, philo_thread, (void *)philo);
	create_thread(&thread_watcher, watcher_routine, (void *)philo);
	detach_thread(thread_philo);
	join_thread(thread_watcher);
	free(pids);
	free(head->args);
	free_philosophers(head);
	exit(EXIT_SUCCESS);
}

static void	*philo_thread(void *data)
{
	sem_t			*sem_fork;
	sem_t			*sem_die;
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	gettimeofday(&philo->timestamp, NULL);
	sem_fork = open_semaphore(SEM_FORKS, philo->args->no_philo);
	sem_die = open_semaphore(philo->custom_sem_name, 1);
	while (philo->no_meals != philo->args->total_no_meals)
		philo_thread_routine(sem_fork, sem_die, philo);
	close_semaphore(sem_fork);
	close_semaphore(sem_die);
	return (NULL);
}

static void	philo_thread_routine(sem_t *sem_fork, sem_t *sem_die,
		t_philosopher *philo)
{
	wait_semaphore(sem_fork);
	state_printer(philo, FORK);
	wait_semaphore(sem_fork);
	state_printer(philo, FORK);
	usleep(100);
	wait_semaphore(sem_die);
	gettimeofday(&philo->timestamp, NULL);
	state_printer(philo, EAT);
	usleep(philo->args->time_to_eat * 1000);
	post_semaphore(sem_die);
	post_semaphore(sem_fork);
	post_semaphore(sem_fork);
	philo->no_meals++;
	state_printer(philo, SLEEP);
	usleep(philo->args->time_to_sleep * 1000);
	state_printer(philo, THINK);
	usleep(1000);
}
