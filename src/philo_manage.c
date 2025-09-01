/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:11:49 by panne-ro          #+#    #+#             */
/*   Updated: 2025/09/01 11:57:34 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *info)
{
	t_philo *philo;

	philo = (t_philo *)info;
	printf("%i thread was create\n", philo->id);
	philo_sleep(philo);
	return NULL;
}

void	philo_sleep(t_philo *philo)
{
	usleep(philo->info->time_to_sleep);
	printf("%d is sleeping\n", philo->id);
}