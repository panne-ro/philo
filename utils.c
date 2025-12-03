/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:22:06 by panne-ro          #+#    #+#             */
/*   Updated: 2025/12/03 10:53:27 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	else
		return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nbr;
	int	minus;

	minus = 0;
	nbr = 0;
	i = 0;
	while (nptr[i] == ' ' || (9 <= nptr[i] && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			minus++;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		nbr = (nbr * 10) + (nptr[i] - '0');
		i++;
	}
	if (minus % 2 == 1)
		nbr = -nbr;
	return (nbr);
}
