/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:14:34 by panne-ro          #+#    #+#             */
/*   Updated: 2025/09/15 00:32:14 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*take_arg(t_philo *philo, char **argv, int nbr_philo, int argc)
{
	int	i;

	i = 0;
	while (i < nbr_philo)
	{
		philo[i].info->time_to_die = ft_atoi(argv[2]);
		philo[i].info->time_to_eat = ft_atoi(argv[3]);
		philo[i].info->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			philo[i].info->max_eat = ft_atoi(argv[5]);
		else
			philo[i].info->max_eat = -1;
		i++;
	}
	return (philo);
}

t_philo	*init_philo(t_philo *philos, int nbr_philo, char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < nbr_philo)
	{
		philos[i].info = malloc(sizeof(t_info));
		philos[i].nbr_philo = nbr_philo;
		philos[i].id = i + 1;
		pthread_mutex_init(&philos[i].fork, NULL);
		pthread_mutex_init(&philos->meals, NULL);
		philos[i].info->philo = philos;
		philos[i].info->stop = 0;
		philos[i].last_meal = get_time_in_ms();
		i++;
	}
	philos = take_arg(philos, argv, nbr_philo, argc);
	return (philos);
}

void *monitor(void *philos)
{
	t_philo *phils;
	int i;
	
	phils = (t_philo *)philos;
	while (1)
	{
		i = 0;
		while (i < phils->nbr_philo)
		{
			if (philo_verif(&phils[i]) != 0)
			{
				pthread_mutex_lock(&phils->info->mutex_stop);
				phils->info->stop = 1;
				pthread_mutex_unlock(&phils->info->mutex_stop);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

void	pthread_use(int nbr_philo, pthread_t *thread, t_philo *philos, pthread_t *monitor_thread)
{
	int	i;
	
	i = 0;
	pthread_create(monitor_thread, NULL, monitor, philos);
	while (i < nbr_philo)
	{
		pthread_create(&thread[i], NULL, routine, &philos[i]);
		ft_usleep(1);
		i++;
	}
	i = 0;
	while (i < nbr_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	pthread_join(*monitor_thread, NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	*thread;
	pthread_t	*monitor_thread;
	t_philo		*philos;
	int			nbr_philo;

	if (argc > 6 || argc < 5)
	{
		printf("too many arguments");
		return (0);
	}
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
	{
		printf("max_eat must be greater than 0");
		return (0);
	}
	nbr_philo = ft_atoi(argv[1]);
	thread = malloc(sizeof(pthread_t) * nbr_philo);
	monitor_thread = malloc(sizeof(pthread_t));
	philos = malloc(sizeof(t_philo) * nbr_philo);
	philos = init_philo(philos, nbr_philo, argv, argc);
	pthread_use(nbr_philo, thread, philos, monitor_thread);
	free(philos);
	free(thread);
	free(monitor_thread);
	return (0);
}
