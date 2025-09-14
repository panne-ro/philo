/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:11:49 by panne-ro          #+#    #+#             */
/*   Updated: 2025/09/15 00:25:53 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *info)
{
	t_philo				*philo;

	philo = (t_philo *)info;
	while (1)
	{
		pthread_mutex_lock(&philo->info->mutex_stop);
		if (philo->info->stop == 1)
		{
			pthread_mutex_unlock(&philo->info->mutex_stop);
			break ;
		}
		pthread_mutex_unlock(&philo->info->mutex_stop);
		printf("%d is thinking\n",philo->id);
		philo_eat(philo);
		pthread_mutex_lock(&philo->info->mutex_stop);
		if (philo->info->stop == 1)
		{
			pthread_mutex_unlock(&philo->info->mutex_stop);
			break ;
		}
		pthread_mutex_unlock(&philo->info->mutex_stop);
		put_forks(philo);
		pthread_mutex_lock(&philo->info->mutex_stop);
		if (philo->info->stop == 1)
		{
			pthread_mutex_unlock(&philo->info->mutex_stop);
			break ;
		}
		pthread_mutex_unlock(&philo->info->mutex_stop);
		philo_sleep(philo);
	}
	return (NULL);
}

void	philo_sleep(t_philo *philo)
{
	printf("%d is sleeping\n", philo->id);
	ft_usleep(philo->info->time_to_sleep);
}

void	take_forks(t_philo *philo)
{
	int		right;

	right = philo->id % philo->nbr_philo;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		printf("%d has taken a fork\n", philo->id);
		pthread_mutex_lock(&philo->info->philo[right].fork);
		printf("%d has taken a fork\n", philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->info->philo[right].fork);
		printf("%d has taken a fork\n", philo->id);
		pthread_mutex_lock(&philo->fork);
		printf("%d has taken a fork\n", philo->id);
	}
}

void	put_forks(t_philo *philo)
{
	int	right;

	right = philo->id % philo->nbr_philo;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->info->philo[right].fork);
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->meals);
	philo->last_meal = get_time_in_ms();
	printf("%d is eating\n", philo->id);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals);
	ft_usleep(philo->info->time_to_eat);
}
