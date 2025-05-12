/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 03:21:52 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/12 23:38:38 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_args(int ac, char **av, t_data *data)
{
	data = malloc(sizeof(t_data));
	data->nbr_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->is_any_dead = 0;
	// data->time;
	if(ac == 5)
		data->must_eat_number = -1;
	else if(ac == 6)
		data->must_eat_number = ft_atoi(av[5]);
}

void	ft_init_mutex()
{
	
}

void	ft_init_philos()
{
	
}

void	ft_init_threads()
{
	
}
