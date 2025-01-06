/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:39:25 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/06 15:38:28 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

sem_t	*open_semaphore(const char *sem_name, uint init_val)
{
	sem_t	*sem;

	sem = sem_open(sem_name, O_CREAT, 0666, init_val);
	if (sem == SEM_FAILED)
	{
		perror("semaphore error"); // remove forbidden func
		exit(EXIT_FAILURE);
	}
	return (sem);
}

void	unlink_semaphore(const char *sem_name)
{
	printf("unlink_semaphore %s\n", sem_name);
	if (sem_unlink(sem_name))
	{
		perror("sem unlink"); // rm forbidden func
		exit(EXIT_FAILURE);
	}
}

void	close_semaphore(sem_t *sem)
{
	printf("close_semaphore\n");
	if (sem_close(sem))
	{
		perror("sem close"); //rm forbidden
		exit(EXIT_FAILURE);
	}
}

void	wait_semaphore(sem_t *sem)
{
	if (sem_wait(sem) == -1)
	{
		perror("sem_wait\n");
		sem_close(sem);
		exit(EXIT_FAILURE);
	}
}

void	post_semaphore(sem_t *sem)
{
	if (sem_post(sem) == -1)
	{
		perror("sem_post\n");
		sem_close(sem);
		exit(EXIT_FAILURE);
	}
}
