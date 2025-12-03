/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:09:39 by panne-ro          #+#    #+#             */
/*   Updated: 2025/12/03 10:29:44 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arg(int argc, char **argv)
{
	int i;
	int	j;

	i = 1;
	if ((argc >= 5) && (argc <= 6))
	{
		while(argv[i])
		{
			j = 0;
			while(argv[i][j])
			{
				if (ft_isdigit(argv[i][j]) == 1)
				{
					printf("Unwanted character in args : %c\n", argv[i][j]);
					return (1);
				}
				j++;
			}
			i++;
		}
		return (0);
	}
	else
		printf("Too Much Arguments\n");
	return (1);
}
