/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:03:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/28 22:01:25 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *ft_threads_routine(void *arg)
{
    t_philo *philo;
    t_data *data;
    
    philo = (t_philo *)arg;
    data = philo->data;
    while (!ft_end_of_sim(data))
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
    while(!ft_end_of_sim(data))
    {
        i = -1;
        while(++i < data->nbr_of_philos)
        {
            
            if(ft_check_end_of_sim(&data->philos[i]))
            {
                ft_destroy_mutex(data);
                ft_destroy_threads(data);
                return(NULL);
            }
        }
    }
    if(ft_end_of_sim(data))
    {
        ft_destroy_mutex(data);
        ft_destroy_threads(data);
    }
    return(NULL);
}
int ft_check_end_of_sim(t_philo *philo)
{
    if(ft_get_time_of_day() - philo->last_eat_time > philo->time_to_die)
    {
        ft_print_action(philo->data, philo->id, "is dead");
        pthread_mutex_lock(&philo->data->lock);
        philo->data->end_of_sim = 1;
        pthread_mutex_unlock(&philo->data->lock);
        return(1);
    }
    if(philo->data->total_eaten == philo->data->must_eat_count)
    {
        pthread_mutex_lock(&philo->data->lock);
        philo->data->end_of_sim = 1;
        pthread_mutex_unlock(&philo->data->lock);
        return(1);
    }
    return(0);
}

int ft_end_of_sim(t_data *data)
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

void    ft_destroy_mutex(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->nbr_of_philos)
        pthread_mutex_destroy(&data->forks[i]);

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