/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:03:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/26 21:23:45 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *ft_threads_routine(void *arg)
{
    t_philo *philo;
    t_data *data;
    
    philo = (t_philo *)arg;
    data = philo->data;
    while (1)
    {
        ft_action_fork(philo);
        ft_action_eat(philo);
        ft_action_sleep(philo);
    }
    return (NULL);
}

void *ft_monitor_routine(void *arg)
{
    t_data *data;
    int i;

    data = (t_data *)arg;
    i = -1;
    while (++i < data->nbr_of_philos)
    {
        if(ft_get_time_of_day() - data->philos[i].last_eat_time > data->philos[i].time_to_die)
        {
            ft_print_action(data, i, "is dead");
            data->philos[i].data->end_of_sim = 1;
            ft_destroy_threads(data);
            ft_destroy_mutex(data);
            return(NULL);
        }
        if(data->total_eaten == data->must_eat_count)
        {
            data->end_of_sim = 1;
            ft_destroy_threads(data);
            ft_destroy_mutex(data);
            return(0);
        }
    }
    return(NULL);
}

void    ft_destroy_mutex(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->nbr_of_philos)
    {
        pthread_mutex_unlock(&data->forks[i]);
        pthread_mutex_destroy(&data->forks[i]);
    }
    pthread_mutex_unlock(&data->eat);
    pthread_mutex_unlock(&data->lock);
    pthread_mutex_unlock(&data->print);
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->eat);
    pthread_mutex_destroy(&data->lock);
    free(data->forks);
}

void    ft_destroy_threads(t_data *data)
{
    int i;
    i = -1;
	while (++i < data->nbr_of_philos)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
			ft_erorr("Thread join fail!");
	}
}