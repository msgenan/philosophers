/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:45:45 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/28 21:57:30 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_action_fork(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->right_fork);
        ft_print_action(philo->data, philo->id, "has taken a fork");
        pthread_mutex_lock(&philo->left_fork);
        ft_print_action(philo->data, philo->id, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->left_fork);
        ft_print_action(philo->data, philo->id, "has taken a fork");
        pthread_mutex_lock(&philo->right_fork);
        ft_print_action(philo->data, philo->id, "has taken a fork");
    }
}

void    ft_action_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->eat);
    ft_print_action(philo->data, philo->id, "is eating");
    usleep(philo->time_to_eat);
    philo->last_eat_time = ft_get_time_of_day();
    philo->meals_eaten++;
    if(philo->meals_eaten == philo->must_eat_count)
    {
        pthread_mutex_lock(&philo->data->lock);
        philo->data->total_eaten++;
        pthread_mutex_unlock(&philo->data->lock);
    }
    pthread_mutex_unlock(&philo->right_fork);
    pthread_mutex_unlock(&philo->left_fork);
    pthread_mutex_unlock(&philo->data->eat);
}

void    ft_action_sleep(t_philo *philo)
{
    ft_print_action(philo->data, philo->id, "is sleeping");
    usleep(philo->data->time_to_sleep);
    ft_print_action(philo->data, philo->id, "is thinking");
}

void    ft_print_action(t_data *data, int id, char *str)
{
    pthread_mutex_lock(&data->print);
    printf("%zu %d %s\n", ft_get_time_of_day() - data->time, id + 1, str);
    pthread_mutex_unlock(&data->print);
}
