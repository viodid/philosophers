/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:55:10 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/07 17:00:59 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE		1
# define FALSE		0
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
	pthread_mutex_t			m_fork;
	pthread_mutex_t			m_die;
	pthread_t				thread;
	uint					thread_no;
	int						no_meals;
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
void		free_philosophers(t_philosopher *philo);
void		philosophers(t_philosopher *head);
void		*watcher_routine(void *data);
void		state_printer(t_philosopher *philo, t_states state);

#endif