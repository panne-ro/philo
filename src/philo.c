/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:14:34 by panne-ro          #+#    #+#             */
/*   Updated: 2025/09/01 12:20:45 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*take_arg(t_philo *philo, char **argv, int nbr_philo)
{
	int	i;

	i = 0;
	while (i < nbr_philo)
	{
		philo[i].info->time_to_die = ft_atoi(argv[2]);
		philo[i].info->time_to_eat = ft_atoi(argv[3]);
		philo[i].info->time_to_sleep = ft_atoi(argv[4]);
		i++;
	}
	return (philo);
}

t_philo	*init_philo(t_philo *philos, int nbr_philo, char **argv)
{
	int	i;

	i = 0;
	while (i < nbr_philo)
	{
		philos[i].info = malloc(sizeof(t_info));
		philos[i].id = i + 1;
		i++;
	}
	philos = take_arg(philos, argv, nbr_philo);
	return (philos);
}

void	pthread_use(int nbr_philo, pthread_t *thread, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < nbr_philo)
	{
		pthread_create(&thread[i], NULL, routine, &philos[i]);
		usleep(1);
		i++;
	}
	i = 0;
	while (i < nbr_philo)
	{
		pthread_join(thread[i], NULL);
		free(philos[i].info);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pthread_t	*thread;
	t_philo		*philos;
	int			nbr_philo;

	if (argc > 6 || argc < 5)
	{
		printf("too many arguments");
		return (0);
	}
	nbr_philo = ft_atoi(argv[1]);
	thread = malloc(sizeof(pthread_t) * nbr_philo);
	philos = malloc(sizeof(t_philo) * nbr_philo);
	philos = init_philo(philos, nbr_philo, argv);
	pthread_use(nbr_philo, thread, philos);
	free(philos);
	free(thread);
	return (0);
}
