/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:47:26 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/30 17:59:23 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static t_args			*allocate_args(int argc, char *argv[]);
static t_philosopher	*allocate_philosophers(t_args *args);
static void				initialize_mutexes(t_philosopher *head);

/* SUBJECT
 * 1. Each philosopher should be a thread.
 * 2. Every philosopher has a fork, i.e. every thread has its own m_fork.
 * 3. The program should prevent the philosophers to die.
 * 4. The process will stop whenever a philosopher dies.
 * 5. For a philosopher to avoid dying, should eat.
 * 6. In order to eat, each philosopher should have 2 forks. If a philosopher
 *    is using one or two forks, no other philosopher could use the same ones.
 * 7. Whenever a philosopher finish eating, he waits idle sleeping.
 * 8. When a philosopher awakes, he can be idle thinking.
 * 9. The time sleeping + the time sitting idle waiting (thinking), should never
 *    be greater than the "time_to_die", otherwise he would die of starvation.
 *
 * The program should be executed as per the following:
* ./philo no_philo time_to_die time_to_eat time_to_sleep total_no_meals(optional)
*/

int	main(int argc, char *argv[])
{
	t_philosopher	*head;
	t_args			*args;

	if (parse_arguments(argc, argv))
	{
		write(2, "Usage: ./philo [no_philo] [time_die] ", 37);
		write(2, "[time_eat] [time_sleep] (must_eat)\n", 36);
		return (EXIT_FAILURE);
	}
	args = allocate_args(argc, argv);
	head = allocate_philosophers(args);
	initialize_mutexes(head);
	philosophers(head);
	free_philosophers(head);
	free(args);
	return (EXIT_SUCCESS);
}

/*
 * Create one struct for every philosopher.
 * Each struct should have a m_fork, the args, and a pointer
 * to the next philosopher. The last node of the linked list
 * should point to the first (circular linked list)
*/
static t_philosopher	*allocate_philosophers(t_args *args)
{
	t_philosopher	*header;
	t_philosopher	*philo;
	uint			i;

	if (args->no_philo == 0)
		return (NULL);
	header = (t_philosopher *) malloc(sizeof(t_philosopher));
	if (!header)
		exit(EXIT_FAILURE);
	philo = header;
	i = 1;
	while (i < args->no_philo)
	{
		philo->next = (t_philosopher *) malloc(sizeof(t_philosopher));
		if (!philo->next)
			exit(EXIT_FAILURE);
		philo->args = args;
		philo->thread_no = i;
		philo = philo->next;
		i++;
	}
	philo->next = header;
	philo->args = args;
	philo->thread_no = i;
	return (header);
}

static t_args	*allocate_args(int argc, char *argv[])
{
	t_args	*output;

	output = (t_args *)malloc(sizeof(t_args));
	if (!output)
		exit(EXIT_FAILURE);
	output->no_philo = ft_u_atoi(argv[1]);
	output->time_to_die = ft_u_atoi(argv[2]);
	output->time_to_eat = ft_u_atoi(argv[3]);
	output->time_to_sleep = ft_u_atoi(argv[4]);
	if (argc == 6)
		output->total_no_meals = (ft_u_atoi(argv[5]));
	else
		output->total_no_meals = -1;
	return (output);
}

static void	initialize_mutexes(t_philosopher *head)
{
	t_philosopher	*philo;

	if (!head)
		return ;
	philo = head;
	while (philo->next != head)
	{
		if (pthread_mutex_init(&philo->m_fork, NULL)
			|| pthread_mutex_init(&philo->m_die, NULL))
			exit(EXIT_FAILURE);
		philo = philo->next;
	}
	if (pthread_mutex_init(&philo->m_fork, NULL)
		|| pthread_mutex_init(&philo->m_die, NULL))
		exit(EXIT_FAILURE);
}
