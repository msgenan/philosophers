/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxc <fxc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:03:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/06/02 00:56:42 by fxc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *ft_threads_routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    while(!ft_is_sim_end(philo->data))
    {
        ft_action_fork(philo);
        if(ft_is_sim_end(philo->data))
            return(NULL);
        ft_action_eat(philo);
        if(ft_is_sim_end(philo->data))
            return(NULL);
        ft_action_sleep(philo);
        if(ft_is_sim_end(philo->data))
            return(NULL);
        ft_action_think(philo);
        if(ft_is_sim_end(philo->data))
            return(NULL);
    }
    return(NULL);
}

void *ft_monitor_routine(void *arg)
{
    t_data *data;
    int i;

    data = (t_data *)arg;
    while (!ft_is_sim_end(data))
    {
        i = -1;
        while (++i < data->nbr_of_philos)
        {
            pthread_mutex_lock(&data->eat);
            if(ft_get_time_of_day() - data->philos[i].last_eat_time >
            data->philos[i].time_to_die)
            {
                pthread_mutex_lock(&data->print);
                printf("%zu %d %s\n", ft_get_time_of_day() - data->time, i + 1, "is dead");
                pthread_mutex_lock(&data->lock);
                data->end_of_sim = 1;
                pthread_mutex_unlock(&data->lock);
                pthread_mutex_unlock(&data->print);
                pthread_mutex_unlock(&data->eat);
                return(NULL);
            }
            pthread_mutex_unlock(&data->eat);
        }
        if(ft_check_all_ate(data))
            break;
    }
    return (NULL);
}

int ft_check_all_ate(t_data *data)
{
    int i;
    int all_ate;
    
    all_ate = 1;
    i = -1;
    if(data->must_eat_count == -1)
        return(0);
    while (++i < data->nbr_of_philos)
    {
        if (data->philos[i].meals_eaten < data->must_eat_count)
        {
            all_ate = 0;
            break;
        }
    }
    pthread_mutex_lock(&data->lock);
    if (data->must_eat_count != -1 && all_ate)
    {
        data->end_of_sim = 1;
        pthread_mutex_unlock(&data->lock);
        return(1);
    }
    pthread_mutex_unlock(&data->lock);
    return(0);
}

int ft_end_of_sim(t_data *data)
{
    int i;
    
    i = -1;
    while (++i < data->nbr_of_philos)
    {
        if(pthread_join(data->threads[i], NULL) != 0)
            ft_erorr("Thread join failed");
    }
    if(pthread_join(data->monitor_thread, NULL) != 0)
		ft_erorr("Thread join failed");
    i = -1;
    while (++i < data->nbr_of_philos)
        pthread_mutex_destroy(&data->forks[i]);
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->eat);
    pthread_mutex_destroy(&data->lock); 
    free(data->forks);
    free(data->threads);
    free(data->philos);
    return(0);
}

int ft_is_sim_end(t_data *data)
{
    int res;

    pthread_mutex_lock(&data->lock);
    res = data->end_of_sim;
    pthread_mutex_unlock(&data->lock);
    return(res);
}

void	ft_usleep(size_t wait_time)
{
	size_t	start;

	start = ft_get_time_of_day();
	while ((ft_get_time_of_day() - start) < wait_time)
		usleep(500);
}
