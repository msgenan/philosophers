/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 03:21:52 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/19 17:53:02 by mugenan          ###   ########.fr       */
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
	data = malloc(sizeof(t_data));
	if (!data)
		ft_erorr("Malloc allocation fail for data!");
	data->nbr_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->time = ft_get_time_of_day();
	data->is_any_dead = 0;
	if(ac == 5)
		data->must_eat_number = -1;
	else
		data->must_eat_number = ft_atoi(av[5]);
	return(0);
}

int	ft_init_philos(t_data *data, t_data *philos)
{
	int i;
	
	i = 0;
	philos = malloc(sizeof(t_data) * data->nbr_of_philos);
	if (!philos)
		ft_erorr("Malloc allocation fail for philos!");
	while (i < data->nbr_of_philos)
	{
		philos[i].id = i;
		philos[i].nbr_of_philos = data->nbr_of_philos;
		philos[i].time_to_die = data->time_to_die;
		philos[i].time_to_eat = data->time_to_eat;
		philos[i].time_to_sleep = data->time_to_sleep;
		i++;
	}
	return(0);
}


int	ft_init_mutex(t_mutex *mutex, int nbr_of_philos)
{
	int	i;

	i = 0;
	mutex->forks = malloc(sizeof(pthread_mutex_t) * nbr_of_philos);
	if(!mutex->forks)
		ft_erorr("Malloc allocation fail for forks mutex!");
	while(i < nbr_of_philos)
	{
		if (pthread_mutex_init(&mutex->forks[i], NULL) != 0)
			ft_erorr("Mutex initialize fail!");
		i++;
	}
	if	(pthread_mutex_init(&mutex->log, NULL) != 0);
			ft_erorr("Mutex initialize fail!");
	if	(pthread_mutex_init(&mutex->print, NULL) != 0);
			ft_erorr("Mutex initialize fail!");
	return(0);
}

int	ft_init_threads(t_data *data, pthread_t *threads)
{
	int i;
	pthread_t	monitor_thread;

	i = 0;
	threads = malloc(sizeof(pthread_t) * data->nbr_of_philos);
	if (!threads)
		ft_erorr("Malloc allocation fail for threads!");
	while (i < data->nbr_of_philos)
	{
		if (pthread_create(&threads[i], NULL, ft_start_threads, NULL) != 0)
			ft_erorr("Thread initialize fail!");
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, ft_monitor_thread, NULL) != 0)
		ft_erorr("Thread initialize fail!");
	return(0);
}
