/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:55:13 by dyunta            #+#    #+#             */
/*   Updated: 2025/01/02 14:03:03 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

void	free_philosophers(t_philosopher *philo)
{
	t_philosopher	*next;
	if (!philo)
		return ;
	while (philo)
	{
		next = philo->next;
		free(philo);
		philo = next;
	}
}
