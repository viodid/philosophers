/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:39:25 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/07 12:54:56 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

sem_t	*open_semaphore(const char *sem_name, uint init_val)
{
	sem_t	*sem;

	sem = sem_open(sem_name, O_CREAT, 0666, init_val);
	if (sem == SEM_FAILED)
		exit(EXIT_FAILURE);
	return (sem);
}

void	unlink_semaphore(const char *sem_name)
{
	if (sem_unlink(sem_name))
		exit(EXIT_FAILURE);
}

void	close_semaphore(sem_t *sem)
{
	if (sem_close(sem))
		exit(EXIT_FAILURE);
}

void	wait_semaphore(sem_t *sem)
{
	if (sem_wait(sem) == -1)
	{
		sem_close(sem);
		exit(EXIT_FAILURE);
	}
}

void	post_semaphore(sem_t *sem)
{
	if (sem_post(sem) == -1)
	{
		sem_close(sem);
		exit(EXIT_FAILURE);
	}
}
