/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:28:19 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/19 17:50:04 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_erorr(char *str)
{
	printf("Erorr: %s\n", str);
	return(1);
}
int	ft_check_args(int ac, char **av)
{
	int i;
	
	i = 1;
	if(ac < 5 || ac > 6)
		return(ft_erorr("Not enough arguments!"));
	while(av[i])
	{
		if(!ft_issdigit(av[i]) || ft_atoi(av[i]) < 1)
			return(ft_erorr("Argument is incorrect!"));
		i++;
	}
	return(0);
}

int main(int ac, char **av)
{
	t_data	*data;
	t_data	*philos;
	t_mutex	*mutex;
	pthread_t *threads;

	data = NULL;
	philos = NULL;
	mutex = NULL;
	if(ft_check_args(ac, av))
		return(EXIT_FAILURE);
	if(ft_init_args(ac, av, data))
		return(EXIT_FAILURE);
	if(ft_init_philos(data, philos))
		return(EXIT_FAILURE);
	if(ft_init_mutex(mutex, data->nbr_of_philos))
		return(EXIT_FAILURE);
	if(ft_init_threads(data, threads))
		return(EXIT_FAILURE);
}
