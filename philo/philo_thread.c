/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:13:43 by lsuau             #+#    #+#             */
/*   Updated: 2022/02/15 18:07:54 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_statu(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->m_alive);
	if (!philo->data->alive)
	{
		pthread_mutex_unlock(&philo->data->m_alive);
		return ;
	}
	pthread_mutex_unlock(&philo->data->m_alive);
	printf("%ld %d%s", le_time() - philo->data->start_time, philo->num, s);
}

void	taking_fork(t_philo *philo)
{
	if (philo->num % 2 && !(philo->data->nb_philo % 2))
	{
		pthread_mutex_lock(&philo->next->fork);
		write_statu(philo, " has taken a fork\n");
		pthread_mutex_lock(&philo->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		write_statu(philo, " has taken a fork\n");
		pthread_mutex_lock(&philo->next->fork);
	}
	write_statu(philo, " has taken a fork\n");
}

void	eat_n_sleep(t_philo *philo)
{
	long	t;

	taking_fork(philo);
	write_statu(philo, " is eating\n");
	pthread_mutex_lock(&philo->m_last_eat);
	philo->last_eat = le_time();
	pthread_mutex_unlock(&philo->m_last_eat);
	t = le_time();
	while (t + philo->data->t_eat > le_time())
		usleep(500);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
	philo->nb_eat++;
	pthread_mutex_lock(&philo->data->m_eat_goal);
	if (philo->nb_eat == philo->data->nb_to_eat)
		philo->data->eat_goal++;
	pthread_mutex_unlock(&philo->data->m_eat_goal);
	write_statu(philo, " is sleeping\n");
	t = le_time();
	while (t + philo->data->t_sleep > le_time())
		usleep(500);
}

void	*le_philo(void *ph)
{
	t_philo	*philo;

	philo = ph;
	while (philo->data->start_time > le_time())
		usleep(100);
	if (philo->num % 2 && !(philo->num == 1 && philo->data->nb_philo % 2))
		eat_n_sleep(philo);
	else
		usleep(10);
	pthread_mutex_lock(&philo->data->m_alive);
	while (philo->data->alive)
	{
		pthread_mutex_unlock(&philo->data->m_alive);
		write_statu(philo, " is thinking\n");
		eat_n_sleep(philo);
		pthread_mutex_lock(&philo->data->m_alive);
	}
	pthread_mutex_unlock(&philo->data->m_alive);
	return (0);
}
