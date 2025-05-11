/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:28:19 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/11 03:46:30 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int main(int ac, char **av)
{
	if(ac < 4 || ac > 6)
		exit(0);
	ft_take_arg(av);
}


// pthread_t	thread1, thread2;
	// if (pthread_create(&thread1, NULL, ft_ilyas, NULL) != 0)
	// 	return(1);
	// if (pthread_create(&thread2, NULL, ft_ilyas, NULL) != 0)
	// 	return(1);
	// pthread_join(thread1, NULL);
	// pthread_join(thread2, NULL);