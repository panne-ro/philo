/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:43:42 by panne-ro          #+#    #+#             */
/*   Updated: 2025/12/03 19:33:42 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				meals_eaten;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	pthread_t		thread;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int					numbers_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	int					is_dead;
	pthread_mutex_t		dead_mutex;
	t_philo				*philo;
}	t_table;


//parse.c
int	parse_arg(int argc, char **argv);

//philo_manage.c
t_table	*init_table(t_table *table, int argc, char **argv);

//utils.c
int	ft_isdigit(char c);
int	ft_atoi(const char *nptr);

#endif