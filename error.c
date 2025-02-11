/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:40:44 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/11 12:24:32 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    ft_error(char *to_write)
{
    write(2, to_write, ft_strlen(to_write));
    exit(1);
}

static void    ft_checkint(const char *str)
{
    int i;

    i = 0;
    while (ft_ispace(str[i]))
        i++;
    if (!(ft_isnum(str[i]) || str[i] == '+'))
        ft_error(FORBID_PARAM);
    if (str[i] == '+')
        i++;
    while (ft_isnum(str[i]))
        i++;
    //Si i est trop grand alors on refuse : ca protege de l'overflow de itoa
    //On peut ensuite préciser au cas par cas dans ft_parser
    if (i >= 7)
       ft_error(LARGE_PARAM); 
    while (ft_ispace(str[i]))
        i++;
    if (str[i])
        ft_error(FORBID_PARAM);
}

void ft_parser(int ac, char **av)
{
    int i;
    
    if (ac != 5 && ac != 6)
        ft_error(PARAM_ERROR);
    i = 0;
    while (av[++i])
        ft_checkint(av[i]);
    //Quelle limitation mettre pour les autres params ?
    if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
        ft_error(TMANY_PHILO);
}