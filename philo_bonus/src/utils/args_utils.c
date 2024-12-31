/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:40:29 by dyunta            #+#    #+#             */
/*   Updated: 2024/12/31 14:04:09 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

static u_int8_t	ft_is_not_num(const char *str)
{
	while (*str)
	{
		if (*str < 48 || *str > 57)
			return (EXIT_FAILURE);
		str++;
	}
	return (EXIT_SUCCESS);
}

u_int8_t	parse_arguments(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	i = 1;
	while (i < argc)
	{
		if (ft_is_not_num(argv[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

// Unsigned atoi, it only should accept an unsigned int represented as a string.
int	ft_u_atoi(char *str)
{
	int		output;
	int		i;

	i = 0;
	output = 0;
	while (str[i])
	{
		output = output * 10 + (int)(str[i] - 48);
		i++;
	}
	return (output);
}
