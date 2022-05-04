/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:43:26 by lsuau             #+#    #+#             */
/*   Updated: 2022/02/15 18:01:26 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_alive);
	philo->data->alive = 0;
	pthread_mutex_unlock(&philo->data->m_alive);
	printf("%ld %d died\n", le_time() - philo->data->start_time, philo->num);
}

void	threadage(t_data *data, t_philo *philo, int x)
{
	pthread_t	t;
	int			n;

	n = x;
	while (n)
	{
		philo = philo->next;
		n--;
	}
	pthread_create(&t, 0, le_philo, philo);
	data->threads[x] = t;
}

void	thread_wait(t_data *data, t_philo *philo)
{
	int	x;

	x = 0;
	while (data->alive)
	{
		pthread_mutex_lock(&philo->m_last_eat);
		if (philo->last_eat + philo->data->t_death < le_time())
			write_death(philo);
		pthread_mutex_unlock(&philo->m_last_eat);
		pthread_mutex_lock(&philo->data->m_eat_goal);
		if (data->eat_goal == data->nb_philo)
		{
			pthread_mutex_lock(&philo->data->m_alive);
			data->alive = 0;
			pthread_mutex_unlock(&philo->data->m_alive);
		}
		pthread_mutex_unlock(&philo->data->m_eat_goal);
		philo = philo->next;
	}
	while (x < data->nb_philo)
	{
		pthread_join(data->threads[x], 0);
		x++;
	}
}

int	special_case(t_data *data, t_philo *philo)
{
	if (data->nb_to_eat == 0)
	{
		philo_clear(philo);
		data_clear(data);
		return (1);
	}
	if (data->nb_philo == 1)
	{
		write(1, "0 1 has taken a fork\n", 21);
		usleep(data->t_death * 1000);
		ft_putnbr_fd(data->t_death, 1);
		write(1, " 1 died\n", 8);
		philo_clear(philo);
		data_clear(data);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int		x;

	if (arg_parse(argc, argv, &data))
		return (l_error());
	data_init(&data);
	philo = philo_init(&data);
	if (!philo || !data.threads)
		return (l_error());
	x = 0;
	if (special_case(&data, philo))
		return (0);
	while (x < data.nb_philo)
	{
		threadage(&data, philo, x);
		x++;
	}
	thread_wait(&data, philo);
	philo_clear(philo);
	data_clear(&data);
}
