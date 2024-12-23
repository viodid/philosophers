/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:55:10 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/23 12:53:42 by dyunta           ###   ########.fr       */
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

u_int8_t	parse_arguments(int argc, char *argv[]);
int			ft_u_atoi(char *str);

#endif