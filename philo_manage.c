/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:33:42 by panne-ro          #+#    #+#             */
/*   Updated: 2025/12/03 19:34:48 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*init_table(t_table *table, int argc, char **argv)
{
	table->numbers_of_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	table->is_dead = 0;
	pthread_mutex_init(&table->dead_mutex, NULL);
	return (table);
}
void	init_philo(t_table *table, int i)
{
	table->philo = malloc (sizeof(t_philo) * table->numbers_of_philo);
	table->philo[i].id = i;
	table->philo[i].last_meal = 0;
	table->philo[i].meals_eaten = 0;
	pthread_mutex_init(&table->philo[i].right_fork, NULL);
	pthread_mutex_init(&table->philo[i].left_fork, NULL);
	table->philo[i].table = table;
}
