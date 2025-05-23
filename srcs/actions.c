/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:45:45 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/24 02:02:53 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_action_fork(t_data *data)
{
    if (data->philos->id % 2 == 0)
    {
        pthread_mutex_lock(&data->philos->right_fork);
        ft_print_action(data, data->philos->id, "has taken a fork");
        pthread_mutex_lock(&data->philos->left_fork);
        ft_print_action(data, data->philos->id, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&data->philos->left_fork);
        ft_print_action(data, data->philos->id, "has taken a fork");
        pthread_mutex_lock(&data->philos->right_fork);
        ft_print_action(data, data->philos->id, "has taken a fork");
    }
}

void    ft_action_eat(t_data *data)
{
    pthread_mutex_lock(&data->eat);
    ft_print_action(data, data->philos->id, "is eating");
    data->philos->last_eat_time = ft_get_time_of_day() - data->philos->time;
    data->philos->meals_eaten++;
    if(data->must_eat_count == data->philos->meals_eaten)
        //end of the program;
    //drop the forks;
    pthread_mutex_unlock(&data->eat);
}

void    ft_action_sleep(t_data *data)
{
    ft_print_action(data, data->philos->id, "is sleeping");
    usleep(data->time_to_sleep);
    ft_print_action(data, data->philos->id, "is thinking");
}


void    ft_print_action(t_data *data, int id, char *str)
{
    pthread_mutex_lock(&data->print);
    printf("%zu %d %s", ft_get_time_of_day() - data->time, id, str);
    pthread_mutex_unlock(&data->print);
}