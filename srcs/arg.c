/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 03:21:52 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/11 03:53:20 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void    ft_take_arg(char **av)
{
    int i;

    i = 1;
    while(av[i])
    {
        if(!((ft_atoi(av[i]) != 0 || av[i] == 0) &&
            (ft_issdigit(av[i]) == 1)))
            exit(1);
        i++;
    }
}

//push_swap argüman alma işlemlerinden yardım al