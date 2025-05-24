/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:03:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/24 22:25:27 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *ft_threads_routine(void *arg)
{
    t_philo *philo;
    t_data *data;
    
    philo = (t_philo *)arg;
    data = philo->data;
    while (ft_check_routine(philo->data))
    {
        ft_action_fork(philo);
        ft_action_eat(philo);
        ft_action_sleep(philo);
        if(ft_get_time_of_day() - philo->last_eat_time >
            philo->time_to_die)
            data->is_someone_dead = philo->id;
        if(philo->meals_eaten == data->must_eat_count)
            data->must_eat = 1;
    }
    return (NULL);
}

void *ft_monitor_routine(void *arg)
{
    t_data *data;

    data = (t_data *)arg;
    while (1)
    {
        if(ft_check_routine(data))
        {
            if(data->is_someone_dead != -1)
                ft_print_action(data, data->is_someone_dead, "died");
            ft_destroy_mutex(data);
            return(NULL);
        }
    }
}

int ft_check_routine(t_data *data)
{
    if (data->is_someone_dead != -1)
        return (1);
    if (data->must_eat == 1)
        return (1);
    return (0);
}

void    ft_destroy_mutex(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->nbr_of_philos)
        pthread_mutex_destroy(&data->forks[i]);
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->eat);
    pthread_mutex_destroy(&data->log);
    free(data->forks);
}
