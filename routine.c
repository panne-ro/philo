/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:35:02 by panne-ro          #+#    #+#             */
/*   Updated: 2025/12/05 12:09:55 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (eating(philo) == 1)
			break ;
		if (dead(philo) == 1)
			break ;
		if (sleeping(philo) == 1)
			break ;
		if (dead(philo) == 1)
			break ;
		if (print_msg(philo, THINK) == 1)
			break ;
		if (dead(philo) == 1)
			break ;	
	}
	return (NULL);
}

int	sleeping(t_philo *philo)
{
	if (print_msg(philo, SLEEP) == 1)
		return (1);
	usleep(philo->table->time_to_sleep * 1000);
	return (0);
}

int	eating(t_philo *philo)
{
	int	right_fork;
	int	left_fork;

	left_fork = philo->index;
	right_fork = (philo->index + 1) % philo->table->numbers_of_philo;
	if (left_fork < right_fork)
	{
		pthread_mutex_lock(&philo->table->fork[left_fork]);
		if (print_msg(philo, FORK) == 1)
		{
			pthread_mutex_unlock(&philo->table->fork[left_fork]);
			return (1);
		}
		pthread_mutex_lock(&philo->table->fork[right_fork]);
		if (print_msg(philo, FORK) == 1)
		{
			pthread_mutex_unlock(&philo->table->fork[left_fork]);
			pthread_mutex_unlock(&philo->table->fork[right_fork]);
			return (1);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->table->fork[right_fork]);
		if (print_msg(philo, FORK) == 1)
		{
			pthread_mutex_unlock(&philo->table->fork[right_fork]);
			return (1);
		}
		pthread_mutex_lock(&philo->table->fork[left_fork]);
		if (print_msg(philo, FORK) == 1)
		{
			pthread_mutex_unlock(&philo->table->fork[right_fork]);
			pthread_mutex_unlock(&philo->table->fork[left_fork]);
			return (1);
		}
	}
	if (print_msg(philo, EAT) == 1)
	{
		pthread_mutex_unlock(&philo->table->fork[right_fork]);
		pthread_mutex_unlock(&philo->table->fork[left_fork]);
		return (1);
	}
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->table->eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->eaten_mutex);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->table->fork[right_fork]);
	pthread_mutex_unlock(&philo->table->fork[left_fork]);
	return (0);
}

int	dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->eaten_mutex);
	if ((get_current_time() - philo->last_meal > philo->table->time_to_die))
	{
		pthread_mutex_lock(&philo->table->dead_mutex);
		philo->table->is_dead = 1;
		pthread_mutex_unlock(&philo->table->dead_mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%lld %i %s", timestamp(philo->table), philo->id, DEAD);
		pthread_mutex_unlock(&philo->table->print_mutex);
		pthread_mutex_unlock(&philo->table->eaten_mutex);
		return (1);
	}
	else if (philo->meals_eaten >= philo->table->must_eat && philo->table->must_eat != -1)
	{
		pthread_mutex_lock(&philo->table->dead_mutex);
		philo->table->is_dead = 1;
		pthread_mutex_unlock(&philo->table->dead_mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		pthread_mutex_unlock(&philo->table->print_mutex);
		pthread_mutex_unlock(&philo->table->eaten_mutex);
		return (1);
	}	
	pthread_mutex_unlock(&philo->table->eaten_mutex);
	return (0);
}
