/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:40:44 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/19 14:39:42 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    ft_checkint(const char *str)
{
    int         i;
    int         j;

    i = 0;
    while (ft_ispace(str[i]))
        i++;
    if (!(ft_isnum(str[i]) || str[i] == '+'))
        ft_error(INV_ARG);
    if (str[i] == '+')
        i++;
    j = 0;
    while (ft_isnum(str[i]))
    {
        i++;
        j++;   
    }
    if (j > 10)
    ft_error(INV_ARG); //INT_MIN = -2 147 483 648       INT_MAX = 2 147 483 647
    while (ft_ispace(str[i]))
        i++;
    if (str[i])
        ft_error(INV_ARG);
    //Peut on mettre certains param a 0 ?
    if (!ft_atol(str))//lancer ft_atol ici permet aussi de verifier qu'on depasse pas l'INT MAX
        ft_error(INV_ARG);  
}

void ft_parser(int ac, char **av)
{
    int i;
    
    if (ac != 5 && ac != 6)
        ft_error(PARAM_ERROR);
    i = 0;
    while (av[++i])
        ft_checkint(av[i]);
    //Quelle(s) limitation(s) mettre pour les autres params ?
    if (ft_atol(av[1]) < 1 || ft_atol(av[1]) > 200)//
        ft_error(TMANY_PHILO);//
    //ASKIP 60 ms minimum pour mourrir dans la correction
}
