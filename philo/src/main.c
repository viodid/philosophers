/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:47:26 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/21 15:24:13 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* SUBJECT
 * 1. Each philosopher should be a thread.
 * 2. Every philosopher has a fork, i.e. every thread has its own mutex.
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
	return (EXIT_SUCCESS);
}
