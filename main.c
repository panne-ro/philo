/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:09:30 by panne-ro          #+#    #+#             */
/*   Updated: 2025/12/05 12:11:36 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		*table;
	int			i;

	if (parse_arg(argc, argv) == 1)
		return (1);
	table = malloc (sizeof(t_table));
	table = init_table(table, argc, argv);
	i = 0;
	while (i < table->numbers_of_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < table->numbers_of_philo)
	{
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&table->dead_mutex);
	free(table->fork);
	free(table->philo);
	free(table);
	return (0);
}
