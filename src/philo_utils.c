/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:16:18 by panne-ro          #+#    #+#             */
/*   Updated: 2025/09/15 00:30:51 by panne-ro         ###   ########.fr       */
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
int	philo_verif(t_philo *philo)
{
	long long	current_time;

	current_time = get_time_in_ms();
	pthread_mutex_lock(&philo->meals);
	if (current_time - philo->last_meal >= philo->info->time_to_die)
	{
		printf("%d died\n", philo->id);
		pthread_mutex_unlock(&philo->meals);
		return (1);
	}
	if (philo->info->max_eat != -1 && philo->meals_eaten >= philo->info->max_eat)
	{
		pthread_mutex_unlock(&philo->meals);
		return (2);
	}
	pthread_mutex_unlock(&philo->meals);
	return (0);
}
