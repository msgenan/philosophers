/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:32:44 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/12 22:59:55 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "../library/lib.h"

typedef struct s_data
{
    int id;
    time_t  time;
    int nbr_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_number;
    int is_any_dead;
}              t_data;

typedef struct s_philo
{
    pthread_mutex_t	*forks;
    pthread_mutex_t *print;
    t_data  *data;
}              t_philo;


int     ft_check_args(int ac, char **av);
void	ft_init_args(int ac, char **av, t_data *data);

#endif