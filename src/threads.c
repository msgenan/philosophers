/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxc <fxc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:03:57 by mugenan           #+#    #+#             */
/*   Updated: 2025/06/24 17:43:08 by fxc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_threads_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!ft_is_sim_end(philo->data))
	{
		ft_action_fork(philo);
		if (ft_is_sim_end(philo->data) || philo->nbr_of_philos == 1)
		{
			if (philo->nbr_of_philos == 1)
				return (NULL);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (NULL);
		}
		ft_action_eat(philo);
		if (ft_is_sim_end(philo->data))
			return (NULL);
		ft_action_sleep(philo);
		if (ft_is_sim_end(philo->data))
			return (NULL);
		ft_action_think(philo);
		if (ft_is_sim_end(philo->data))
			return (NULL);
	}
	return (NULL);
}

void	*ft_monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!ft_is_sim_end(data))
	{
		i = -1;
		while (++i < data->nbr_of_philos)
		{
			if (ft_get_time_of_day() - data->philos[i].last_eat_time
				> data->philos[i].time_to_die)
			{
				ft_print_action(data, i, "is dead");
				ft_set_end_of_sim(data);
				return (NULL);
			}
		}
		if (ft_check_all_ate(data))
			break ;
	}
	return (NULL);
}

void	ft_set_end_of_sim(t_data *data)
{
	pthread_mutex_lock(&data->lock);
	data->end_of_sim = 1;
	pthread_mutex_unlock(&data->lock);
}

int	ft_check_all_ate(t_data *data)
{
	int	i;
	int	all_ate;

	all_ate = 1;
	i = -1;
	if (data->must_eat_count == -1)
		return (0);
	while (++i < data->nbr_of_philos)
	{
		pthread_mutex_lock(&data->eat);
		if (data->philos[i].meals_eaten < data->must_eat_count)
		{
			all_ate = 0;
			pthread_mutex_unlock(&data->eat);
			break ;
		}
		pthread_mutex_unlock(&data->eat);
	}
	if (data->must_eat_count != -1 && all_ate)
	{
		ft_set_end_of_sim(data);
		return (1);
	}
	return (0);
}

int	ft_end_of_sim(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_of_philos)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
			ft_erorr("Thread join failed");
	}
	if (pthread_join(data->monitor_thread, NULL) != 0)
		ft_erorr("Thread join failed");
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->lock);
	free(data->forks);
	free(data->threads);
	free(data->philos);
	return (0);
}
