/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:28:19 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/23 22:29:30 by mugenan          ###   ########.fr       */
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
	t_data	data;

	if(ft_check_args(ac, av))
		return(EXIT_FAILURE);
	if(ft_init_args(ac, av, &data))
		return(EXIT_FAILURE);
	if(ft_init_mutex(&data))
		return(EXIT_FAILURE);
	if(ft_init_philos(&data))
		return(EXIT_FAILURE);
	if(ft_init_threads(&data))
		return(EXIT_FAILURE);
}
