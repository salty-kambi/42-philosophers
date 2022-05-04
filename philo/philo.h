/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:29:06 by lsuau             #+#    #+#             */
/*   Updated: 2022/02/15 18:20:08 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int				nb_philo;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				nb_to_eat;
	int				alive;
	pthread_mutex_t	m_alive;
	int				eat_goal;
	pthread_mutex_t	m_eat_goal;
	long			start_time;
	pthread_t		*threads;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				num;
	long			last_eat;
	pthread_mutex_t	m_last_eat;
	int				nb_eat;
	pthread_mutex_t	fork;
	struct s_philo	*next;
}	t_philo;

t_philo	*philo_init(t_data *data);
int		arg_parse(int argc, char **argv, t_data *data);
int		ft_atoi(const char *str);
int		l_error(void);
void	philo_clear(t_philo *philo);
void	data_init(t_data *data);
void	data_clear(t_data *data);
void	*le_philo(void *ph);
long	le_time(void);
void	write_statu(t_philo *philo, char *s);
void	write_death(t_philo *philo);
void	ft_putnbr_fd(int n, int fd);

#endif