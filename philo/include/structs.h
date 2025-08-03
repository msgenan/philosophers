/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:58:11 by mugenan           #+#    #+#             */
/*   Updated: 2025/06/02 14:50:19 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				end_of_sim;
	size_t			time_to_die;
	int				time_to_eat;
	int				nbr_of_philos;
	int				time_to_sleep;
	int				must_eat_count;
	size_t			time;
	t_philo			*philos;
	pthread_t		*threads;
	pthread_t		monitor_thread;
	pthread_mutex_t	eat;
	pthread_mutex_t	lock;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				time_to_eat;
	int				meals_eaten;
	size_t			time_to_die;
	int				time_to_sleep;
	int				nbr_of_philos;
	int				must_eat_count;
	size_t			time;
	size_t			last_eat_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

#endif
