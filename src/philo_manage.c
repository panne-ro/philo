/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:11:49 by panne-ro          #+#    #+#             */
/*   Updated: 2025/09/08 18:31:30 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *info)
{
	t_philo			*philo;
	long long		now;

	philo = (t_philo *)info;
	while (philo->info->stop == 0)
	{
		now = get_time_in_ms();
		if(now - philo->last_meal > philo->info->time_to_die)
		{
			printf("%d died\n", philo->id);
			philo->info->stop = 1;
			break ;
		}
		if (philo->info->max_eat != -1 && philo->meals_eaten >= philo->info->max_eat)
		{
			printf("%d has eaten %d times\n", philo->id, philo->meals_eaten);
			philo->info->stop = 1;
			break ;
		}
		printf("%d is thinking\n",philo->id);
		philo_eat(philo);
		put_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	philo_sleep(t_philo *philo)
{
	printf("%d is sleeping\n", philo->id);
	ft_usleep(philo->info->time_to_sleep, philo);
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
	printf("%d is eating\n", philo->id);
	philo->meals_eaten++;
	philo->last_meal = get_time_in_ms();
	ft_usleep(philo->info->time_to_eat, philo);
}