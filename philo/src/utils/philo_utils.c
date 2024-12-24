/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:40:26 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/24 18:01:24 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	free_philosophers(t_philosopher *philo)
{
	t_philosopher	*next_philo;

	while (philo->next)
	{
		next_philo = philo->next;
		free(philo);
		philo = NULL;
		philo = next_philo;
	}
}
