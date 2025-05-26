/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:32:44 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/26 21:25:28 by mugenan          ###   ########.fr       */
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

typedef struct s_philo t_philo;

typedef struct s_data
{
    int dead_id;
    int end_of_sim;
    int total_eaten;
    int time_to_die;
    int time_to_eat;
    int nbr_of_philos;
    int time_to_sleep;
    int must_eat_count;
    size_t  time;
    t_philo *philos;
    pthread_t *threads;
    pthread_mutex_t eat;
    pthread_mutex_t lock;
    pthread_mutex_t print;
    pthread_mutex_t	*forks;
}              t_data;

typedef struct s_philo
{
    int id;
    int time_to_eat;
    int meals_eaten;
    int time_to_sleep;
    int nbr_of_philos;
    int must_eat_count;
    int is_philo_dead;
    size_t  time;
    size_t time_to_die;
    size_t  last_eat_time;
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
    t_data *data;
}               t_philo;

int     ft_erorr(char *str);
size_t	ft_get_time_of_day(void);
int     ft_check_args(int ac, char **av);
int     ft_routine_control(t_philo *philo);
void    ft_destroy_mutex(t_data *data);
void    ft_destroy_threads(t_data *data);

/* initialize.c */
int     ft_init_args(int ac, char **av, t_data *data);
int     ft_init_philos(t_data *data);
int     ft_init_mutex(t_data *data);
int     ft_init_threads(t_data *data);

/* threads.c */
void    *ft_threads_routine(void *arg);
void *ft_monitor_routine(void    *arg);

/* actions.c */
void    ft_action_fork(t_philo *philo);
void    ft_action_eat(t_philo *philo);
void    ft_action_sleep(t_philo *philo);
void    ft_print_action(t_data *data, int id, char *str);

#endif