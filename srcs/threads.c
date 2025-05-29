/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:03:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/29 19:30:10 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *ft_threads_routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    while(!ft_is_any_dead(philo->data))
    {
        ft_action_fork(philo);
        if(ft_is_any_dead(philo->data))
            return(NULL);
        ft_action_eat(philo);
        if(ft_is_any_dead(philo->data))
            return(NULL);
        ft_action_sleep(philo);
        if(ft_is_any_dead(philo->data))
            return(NULL);
        ft_action_think(philo);
        if(ft_is_any_dead(philo->data))
            return(NULL);
    }
    return(NULL);
}

void *ft_monitor_routine(void *arg)
{
    t_data *data;
    int i;

    data = (t_data *)arg;
    while (!ft_is_any_dead(data))
    {
        i = -1;
        while (++i < data->nbr_of_philos)
        {
            if (ft_is_philo_starve(&data->philos[i]))
                return (NULL);
        }
        if (ft_is_philos_eat_enough(data))
            return (NULL);
        usleep(1000); // CPU dostu kontrol aralığı
    }
    return (NULL);
}

int ft_is_philos_eat_enough(t_data *data)
{
    int i;
    int full_count = 0;

    if (data->must_eat_count <= 0)
        return (0);
    
    pthread_mutex_lock(&data->eaten);
    i = -1;
    while (++i < data->nbr_of_philos)
    {
        if (data->philos[i].meals_eaten >= data->must_eat_count)
            full_count++;
    }
    if (full_count == data->nbr_of_philos)
    {
        pthread_mutex_lock(&data->lock);
        data->end_of_sim = 1;
        pthread_mutex_unlock(&data->lock);
        pthread_mutex_unlock(&data->eaten);
        return (1);
    }
    pthread_mutex_unlock(&data->eaten);
    return (0);
}


int ft_is_philo_starve(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->time_lock);
    if(ft_get_time_of_day() - philo->last_eat_time  >
        philo->time_to_die)
    {
        ft_print_action(philo->data, philo->id, "is dead");
        pthread_mutex_lock(&philo->data->lock);
        philo->data->end_of_sim = 1;
        pthread_mutex_unlock(&philo->data->lock);
        pthread_mutex_unlock(&philo->data->time_lock);
        return(1);
    }
    pthread_mutex_unlock(&philo->data->time_lock);
    return(0);
}

void ft_end_of_sim(t_data *data)
{
    int i = -1;

    while (++i < data->nbr_of_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
    }

    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->eat);
    pthread_mutex_destroy(&data->lock);
    pthread_mutex_destroy(&data->time_lock);
    pthread_mutex_destroy(&data->eaten);

    free(data->forks);
    free(data->threads);
    free(data->philos);
}


int ft_is_any_dead(t_data *data)
{
    pthread_mutex_lock(&data->lock);
    if(data->end_of_sim == 1)
    {
        pthread_mutex_unlock(&data->lock);
        return(1);
    }
    pthread_mutex_unlock(&data->lock);
    return(0);
}

void	ft_usleep(size_t wait_time)
{
	size_t	start;

	start = ft_get_time_of_day();
	while ((ft_get_time_of_day() - start) < wait_time)
		usleep(500);
}
