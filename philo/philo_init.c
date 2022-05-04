/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:45:08 by lsuau             #+#    #+#             */
/*   Updated: 2022/02/15 18:02:06 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_new(t_data *data, int x)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (0);
	new->data = data;
	new->num = x;
	pthread_mutex_init(&new->fork, NULL);
	new->last_eat = data->start_time;
	pthread_mutex_init(&new->m_last_eat, NULL);
	new->nb_eat = 0;
	new->next = 0;
	return (new);
}

void	philo_addback(t_philo **philo, t_philo *new)
{
	t_philo	*t;

	if (!*philo)
	{
		*philo = new;
		return ;
	}
	t = *philo;
	while (t->next)
		t = t->next;
	t->next = new;
}

void	philo_clear(t_philo *philo)
{
	t_philo	*t;
	int		x;
	int		nb_philo;

	x = 0;
	nb_philo = philo->data->nb_philo;
	while (x < nb_philo)
	{
		t = philo->next;
		pthread_mutex_destroy(&philo->fork);
		pthread_mutex_destroy(&philo->m_last_eat);
		free(philo);
		philo = t;
		x++;
	}
}

t_philo	*philo_init(t_data *data)
{
	t_philo	*philo;
	t_philo	*t;
	int		x;

	x = 1;
	philo = 0;
	while (x <= data->nb_philo)
	{
		t = philo_new(data, x);
		philo_addback(&philo, t);
		if (!t)
		{
			philo_clear(philo);
			return (0);
		}
		x++;
	}
	t->next = philo;
	return (philo);
}
