/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:32:44 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/03 19:55:17 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"

int		ft_erorr(char *str);
int		ft_check_args(int ac, char **av);

size_t	ft_get_time_of_day(void);
int		ft_issdigit(char *str);
int		ft_atoi(const char *str);
int		ft_is_sim_end(t_data *data);
void	ft_usleep(size_t wait_time, t_data *data);

int		ft_init_mutex(t_data *data);
int		ft_init_philos(t_data *data);
int		ft_init_threads(t_data *data);
int		ft_init_args(int ac, char **av, t_data *data);

int		ft_end_of_sim(t_data *data);
int		ft_check_all_ate(t_data *data);
void	*ft_threads_routine(void *arg);
void	ft_set_end_of_sim(t_data *data);
void	*ft_monitor_routine(void *arg);

void	ft_action_eat(t_philo *philo);
void	ft_action_fork(t_philo *philo);
void	ft_action_sleep(t_philo *philo);
void	ft_action_think(t_philo *philo);
void	ft_print_action(t_data *data, int id, char *str);

#endif
