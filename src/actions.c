/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:45:45 by mugenan           #+#    #+#             */
/*   Updated: 2025/06/02 15:29:33 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_action_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		ft_print_action(philo->data, philo->id, "has taken a fork");
		if (philo->nbr_of_philos == 1)
		{
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
		pthread_mutex_lock(philo->left_fork);
		ft_print_action(philo->data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_action(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		ft_print_action(philo->data, philo->id, "has taken a fork");
	}
}

void	ft_action_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat);
	philo->last_eat_time = ft_get_time_of_day();
	pthread_mutex_unlock(&philo->data->eat);
	ft_print_action(philo->data, philo->id, "is eating");
	ft_usleep(philo->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->data->eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	ft_action_sleep(t_philo *philo)
{
	if (ft_is_sim_end(philo->data))
		return ;
	ft_print_action(philo->data, philo->id, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	ft_action_think(t_philo *philo)
{
	if (ft_is_sim_end(philo->data))
		return ;
	ft_print_action(philo->data, philo->id, "is thinking");
}

void	ft_print_action(t_data *data, int id, char *str)
{
	pthread_mutex_lock(&data->print);
	if (ft_is_sim_end(data))
	{
		pthread_mutex_unlock(&data->print);
		return ;
	}
	printf("%zu %d %s\n", ft_get_time_of_day() - data->time, id + 1, str);
	pthread_mutex_unlock(&data->print);
}
