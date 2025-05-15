/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 03:21:52 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/15 03:49:26 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_get_time_of_day(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return((size_t)(tv.tv_sec) * 1000 + (size_t)(tv.tv_usec) / 1000);
}

void	ft_init_args(int ac, char **av, t_data *data)
{
	data = malloc(sizeof(t_data));
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
}

void	ft_init_philos(t_data *data, t_data *philos)
{
	int i;
	
	i = 0;
	philos = malloc(sizeof(t_data) * data->nbr_of_philos);
	while (i < data->nbr_of_philos)
	{
		philos[i].id = i;
		philos[i].nbr_of_philos = data->nbr_of_philos;
		philos[i].time_to_die = data->time_to_die;
		philos[i].time_to_eat = data->time_to_eat;
		philos[i].time_to_sleep = data->time_to_sleep;
		i++;
	}
}

void	ft_init_threads(t_data *data, pthread_t *threads)
{
	int i;
	pthread_t	monitor_thread;

	i = 0;
	threads = malloc(sizeof(pthread_t) * data->nbr_of_philos);
	while (i < data->nbr_of_philos)
	{
		pthread_create(&threads[i], NULL, ft_start_threads, NULL);
		i++;
	}
	pthread_create(&monitor_thread, NULL, ft_monitor_thread, NULL);
}

void	ft_init_mutex(t_mutex *)
{
	int	i;
	
}
