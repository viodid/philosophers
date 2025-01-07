/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:55:10 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/06 18:58:42 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define TRUE		1
# define FALSE		0
# define SEM_FORKS	"/forks"
# define SEM_DIE	"/die"
# define RED_BOLD	"\001\033[1;31m\002"
# define GRN_BOLD	"\001\033[1;32m\002"
# define X_BOLD		"\001\033[1;33m\002"
# define BLU_BOLD	"\001\033[1;34m\002"
# define Y_BOLD		"\001\033[1;35m\002"
# define RES		"\001\033[0m\002"

typedef struct timeval	t_timeval;

// Args struct to parse only once and track the arguments
typedef struct s_args
{
	uint	no_philo;
	uint	time_to_die;
	uint	time_to_eat;
	uint	time_to_sleep;
	int		total_no_meals;
}	t_args;

typedef struct s_philosopher
{
	t_args					*args;
	int						no_meals;
	uint					process_no;
	t_timeval				timestamp;
	struct s_philosopher	*next;
}	t_philosopher;

typedef enum e_states
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED
}	t_states;

u_int8_t	parse_arguments(int argc, char *argv[]);
int			ft_u_atoi(char *str);
void		philosophers(t_philosopher *header);
void		*watcher_routine(void *data);
void		state_printer(t_philosopher *philo, t_states state);
void		free_philosophers(t_philosopher *philo);
sem_t		*open_semaphore(const char *sem_name, uint init_val);
void		unlink_semaphore(const char *sem_name);
void		close_semaphore(sem_t *sem);
void		wait_semaphore(sem_t *sem);
void		post_semaphore(sem_t *sem);
void		create_thread(pthread_t* thread, void *routine, void *payload);
void		join_thread(pthread_t thread);
void		detach_thread(pthread_t thread);
void		*wait_process(void *data);

#endif