/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:16:18 by panne-ro          #+#    #+#             */
/*   Updated: 2025/09/01 18:29:07 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		nbr;
	int		sign;

	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == 45)
	{
		sign = -1;
		i++;
	}
	else if (str[i] == 43)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

int	ft_usleep(long long time)
{
	struct timeval	start_tv;
	struct timeval	now_tv;
	long long		start;
	long long		now;

	gettimeofday(&start_tv, NULL);
	start = start_tv.tv_sec * 1000LL + start_tv.tv_usec / 1000;
	while (1)
	{
		gettimeofday(&now_tv, NULL);
		now = now_tv.tv_sec * 1000LL + now_tv.tv_usec / 1000;
		if (now - start >= time)
			break ;
		usleep(50);
	}
	return (0);
}

long long get_time_in_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}
