/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:33:42 by panne-ro          #+#    #+#             */
/*   Updated: 2025/12/05 12:09:49 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*init_table(t_table *table, int argc, char **argv)
{
	table->numbers_of_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->start_time = get_current_time();
	if (argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	table->is_dead = 0;
	pthread_mutex_init(&table->dead_mutex, NULL);
	pthread_mutex_init(&table->eaten_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	init_philo(table);
	return (table);
}

void	init_philo(t_table *table)
{
	int	i;

	table->philo = malloc (sizeof(t_philo) * table->numbers_of_philo);
	table->fork = malloc (sizeof (pthread_mutex_t) * table->numbers_of_philo);
	i = 0;
	while (i < table->numbers_of_philo)
		pthread_mutex_init(&table->fork[i++], NULL);
	i = 0;
	while (i < table->numbers_of_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].index = i;
		table->philo[i].last_meal = get_current_time();
		table->philo[i].meals_eaten = 0;
		table->philo[i].table = table;
		i++;
	}
	i = 0;
	while (i < table->numbers_of_philo)
	{
		pthread_create(&table->philo[i].thread, NULL, life, &table->philo[i]);
		i++;
	}
}
int	print_msg(t_philo *philo, char *msg)
{
	dead(philo);
	pthread_mutex_lock(&philo->table->dead_mutex);
	if (philo->table->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->table->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->dead_mutex);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lld %i %s", timestamp(philo->table), philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (0);
}
