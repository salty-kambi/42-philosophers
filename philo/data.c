/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:14:39 by lsuau             #+#    #+#             */
/*   Updated: 2022/02/15 17:56:18 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	le_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	data_clear(t_data *data)
{	
	pthread_mutex_destroy(&data->m_alive);
	pthread_mutex_destroy(&data->m_eat_goal);
	free(data->threads);
}

void	data_init(t_data *data)
{
	data->threads = malloc(sizeof(pthread_t) * data->nb_philo);
	data->alive = 1;
	pthread_mutex_init(&data->m_alive, NULL);
	pthread_mutex_init(&data->m_eat_goal, NULL);
	data->eat_goal = 0;
	data->start_time = le_time() + 1;
}
