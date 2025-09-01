/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:13:32 by panne-ro          #+#    #+#             */
/*   Updated: 2025/09/01 18:28:55 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	struct s_info	*info;
	int				id;
	int				nbr_philo;
	long long int	last_meal;
	pthread_mutex_t	fork;
}	t_philo;

typedef struct s_info
{
	int		time_to_sleep;
	int		time_to_eat;
	int		time_to_die;
	t_philo	*philo;
}	t_info;

//philo_manage.c
void		*routine(void *info);
void		philo_sleep(t_philo *philo);
void		take_forks(t_philo *philo);
void		put_forks(t_philo *philo);

//philo.c
t_philo		*take_arg(t_philo *philo, char **argv, int nbr_philo);
t_philo		*init_philo(t_philo *philos, int nbr_philo, char **argv);
void		pthread_use(int nbr_philo, pthread_t *thread, t_philo *philos);
int			main(int argc, char **argv);

//philo_utils.c
int			ft_atoi(const char *str);
int			ft_usleep(long long time);
long long	get_time_in_ms(void);

#endif