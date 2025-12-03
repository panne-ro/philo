/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:09:30 by panne-ro          #+#    #+#             */
/*   Updated: 2025/12/03 19:34:32 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	
	if (parse_arg(argc, argv) == 1)
		return (1);
	table = malloc (sizeof(t_table));
	table = init_table(table, argc, argv);
	free(table);
	return (0);
}
