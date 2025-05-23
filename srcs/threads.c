/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:03:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/24 02:00:53 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *ft_threads_routine(void *arg)
{
    t_data *data;
    
    data = (t_data *)arg;
    
}

void *ft_monitor_thread(void    *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (1)
    {
        i = 0;
        while (i < data->nbr_of_philos)
        {
            pthread_mutex_lock(&data->log);
            if (ft_is_philo_starve(data, i))
            {
                //philos dead!
            }
            pthread_mutex_unlock(&data->log);
            i++;
        }
        usleep(500);
    }
}

int	ft_is_philo_starve(t_data *data, int i)
{
	if (ft_get_time_of_day() - data->philos[i].last_eat_time
			> data->time_to_die)
		return(1);
	return(0);
}