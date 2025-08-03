/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:26:17 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/03 19:58:20 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_sim_end(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->lock);
	res = data->end_of_sim;
	pthread_mutex_unlock(&data->lock);
	return (res);
}

void	ft_usleep(size_t wait_time, t_data *data)
{
	size_t	start;

	start = ft_get_time_of_day();
	while ((ft_get_time_of_day() - start) < wait_time)
	{
		if (ft_is_sim_end(data))
			break ;
		usleep(100);
	}
}

size_t	ft_get_time_of_day(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((size_t)(tv.tv_sec) * 1000 + (size_t)(tv.tv_usec) / 1000);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	size_t		result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = (result * 10) + (str[i++] - '0');
		if (result > 2147483647)
			return (0);
	}
	if (result)
		return ((int)(result * sign));
	return (0);
}

int	ft_issdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '+'))
			return (0);
		i++;
	}
	return (1);
}
