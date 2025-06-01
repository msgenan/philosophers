/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxc <fxc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 03:21:52 by mugenan           #+#    #+#             */
/*   Updated: 2025/06/02 00:53:55 by fxc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_get_time_of_day(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return((size_t)(tv.tv_sec) * 1000 + (size_t)(tv.tv_usec) / 1000);
}

int	ft_init_args(int ac, char **av, t_data *data)
{
	data->end_of_sim = 0;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->nbr_of_philos = ft_atoi(av[1]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->time = ft_get_time_of_day();
	if(ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	else
		data->must_eat_count = -1;
	return(0);
}

int	ft_init_mutex(t_data *data)
{
	int	i;
	
	i = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philos);
	if(!data->forks)
		ft_erorr("Malloc allocation fail for forks mutex!");
	while(++i < data->nbr_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		ft_erorr("Mutex initialize fail!");
	}
	if	(pthread_mutex_init(&data->lock, NULL) != 0)
		ft_erorr("Mutex initialize fail!");
	if	(pthread_mutex_init(&data->print, NULL) != 0)
		ft_erorr("Mutex initialize fail!");
	if	(pthread_mutex_init(&data->eat, NULL) != 0)
		ft_erorr("Mutex initialize fail!");
	// if	(pthread_mutex_init(&data->, NULL) != 0)
	// 	ft_erorr("Mutex initialize fail!");
	return(0);
}

int	ft_init_philos(t_data *data)
{
	int i;
	
	i = -1;
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!data->philos)
		ft_erorr("Malloc allocation fail for philos!");
	while (++i < data->nbr_of_philos)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].time = ft_get_time_of_day();
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].nbr_of_philos = data->nbr_of_philos;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		data->philos[i].last_eat_time = data->philos[i].time;
		data->philos[i].must_eat_count = data->must_eat_count;
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->nbr_of_philos];
		data->philos[i].data = data;
	}
	return(0);
}

int	ft_init_threads(t_data *data)
{
	int i;

	i = -1;
	data->threads = malloc(sizeof(pthread_t) * data->nbr_of_philos);
	if (!data->threads)
		ft_erorr("Malloc allocation fail for threads!");
	while (++i < data->nbr_of_philos)
	{
		if (pthread_create(&data->threads[i], NULL, ft_threads_routine, (void *)&data->philos[i]) != 0)
			ft_erorr("Thread initialize fail!");
	}
	if (pthread_create(&data->monitor_thread, NULL, ft_monitor_routine, (void *)data) != 0)
		ft_erorr("Thread initialize fail!");
	return(0);
}
