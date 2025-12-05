/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:43:42 by panne-ro          #+#    #+#             */
/*   Updated: 2025/12/05 15:40:01 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FORK "has taken a fork\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DEAD "died\n"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				meals_eaten;
	int				index;
	int				is_dead;
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
	long long			start_time;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		eaten_mutex;		
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		*fork;
	t_philo				*philo;
}	t_table;

//parse.c
int			parse_arg(int argc, char **argv);

//philo_manage.c
t_table		*init_table(t_table *table, int argc, char **argv);
void		init_philo(t_table *table);
int			print_msg(t_philo *philo, char *msg);
int	all_eat(t_table *table);

//routine.c
void		*life(void *arg);
int		sleeping(t_philo *philo);
int		eating(t_philo *philo);
int			dead(t_table *table);

//utils.c
int			ft_isdigit(char c);
int			ft_atoi(const char *nptr);
long long	get_current_time(void);
long long	timestamp(t_table *table);

#endif