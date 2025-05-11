/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 03:21:52 by mugenan           #+#    #+#             */
/*   Updated: 2025/05/11 15:12:00 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_take_arg(char **av)
{
    int i;
    int num;
    
    i = 1;
    while(av[i])
    {
        num = ft_atoi(av[i]);
        if(!(num != 0 || av[i] == 0))
            printf("argument is incorrect!\n");
        else if(num > 2147483647)
            printf("argument is over max_int!\n");
        else if(!ft_issdigit(av[i]))
            printf("argument has a char!\n");
        i++;
    }
}
