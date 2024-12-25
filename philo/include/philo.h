/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:55:10 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/25 10:48:16 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
#define PHILO
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

typedef struct timeval t_timeval;

// Args struct to parse only once and track the arguments
typedef struct s_args {
	uint	no_philo;
	uint	time_to_die;
	uint	time_to_eat;
	uint	time_to_sleep;
	int		total_no_meals;
}	t_args;

typedef struct s_philosopher {
	t_args					*args;
	pthread_mutex_t			mutex;
	pthread_t				thread;
	uint					thread_no;
	t_timeval				timestamp;
	struct s_philosopher	*next;
}	t_philosopher;


u_int8_t	parse_arguments(int argc, char *argv[]);
int			ft_u_atoi(char *str);
void		free_philosophers(t_philosopher *philo);
void		philosophers(t_philosopher *head);

#endif