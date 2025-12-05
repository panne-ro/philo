/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:35:02 by panne-ro          #+#    #+#             */
/*   Updated: 2025/12/05 15:42:50 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	
	while (1)
	{
		pthread_mutex_lock(&philo->table->dead_mutex);
		if (philo->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->table->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->dead_mutex);
		eating(philo);
		sleeping(philo);
		print_msg(philo, THINK);
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
	philo->last_meal = get_current_time();
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->table->eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->eaten_mutex);
	pthread_mutex_unlock(&philo->table->fork[right_fork]);
	pthread_mutex_unlock(&philo->table->fork[left_fork]);
	return (0);
}

int	dead(t_table *table)
{
	int i;
	
	i = 0;
	while (i < table->numbers_of_philo)
	{
		pthread_mutex_lock(&table->eaten_mutex);
		if((get_current_time() - table->philo[i].last_meal) > table->time_to_die)
		{
			pthread_mutex_unlock(&table->eaten_mutex);
			return (1);
		}
		pthread_mutex_unlock(&table->eaten_mutex);
		i++;
	}
	return (0);
}
