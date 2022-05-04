/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:00:23 by lsuau             #+#    #+#             */
/*   Updated: 2022/02/08 19:49:04 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	l_error(void)
{
	write(2, "Error\n", 6);
	return (0);
}

int	check_num(int argc, char **argv)
{
	int	x;
	int	y;

	x = 1;
	while (x < argc)
	{
		y = 0;
		while (argv[x][y])
		{
			if (!(argv[x][y] >= '0' && argv[x][y] <= '9'))
				return (1);
			y++;
		}
		if (ft_atoi(argv[x]) == -1)
			return (1);
		x++;
	}
	return (0);
}

int	arg_parse(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (1);
	data->nb_to_eat = -1;
	if (check_num(argc, argv))
		return (1);
	data->nb_philo = ft_atoi(argv[1]);
	data->t_death = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_to_eat = ft_atoi(argv[5]);
	if (data->nb_philo < 1)
		return (1);
	return (0);
}
