/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:32:44 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/24 01:42:56 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "../library/lib.h"

typedef struct s_data
{
    size_t  time;
    int nbr_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_count;
    int is_someone_dead;
    t_philo *philos;
    pthread_t *threads;
    pthread_mutex_t	*forks;
    pthread_mutex_t print;
    pthread_mutex_t eat;
    pthread_mutex_t log;
}              t_data;

typedef struct s_philo
{
    int id;
    size_t  time;
    int nbr_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int last_eat_time;
    int meals_eaten;
    pthread_mutex_t right_fork;
    pthread_mutex_t left_fork;

}               t_philo;

int     ft_erorr(char *str);
size_t	ft_get_time_of_day(void);
int     ft_check_args(int ac, char **av);


int     ft_init_args(int ac, char **av, t_data *data);
int     ft_init_philos(t_data *data);
int     ft_init_mutex(t_data *data);
int     ft_init_threads(t_data *data);

void    *ft_threads_routine(void *arg);
void    *ft_monitor_thread(void *arg);

#endif