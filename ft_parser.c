/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:40:44 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/05 11:56:04 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int     ft_isnum(const char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

static int     ft_ispace(const char c)
{
    if (c == ' ' || c == '\n' || c == '\t')
        return (1);
    return (0);
}

static void    ft_checkint(const char *str, int n_arg)
{
    int         i;
    int         j;

    i = 0;
    while (ft_ispace(str[i]))
        i++;
    if (!(ft_isnum(str[i]) || str[i] == '+'))
        ft_exit(INV_ARG);
    if (str[i] == '+')
        i++;
    j = 0;
    while (ft_isnum(str[i]))
    {
        i++;
        j++;   
    }
    if (j > 10)
       ft_exit(INV_ARG); //INT_MIN = -2 147 483 648       INT_MAX = 2 147 483 647
    while (ft_ispace(str[i]))
        i++;
    if (str[i])
        ft_exit(INV_ARG);
    //Peut on mettre certains param a 0 ?
    //Jusqu'ici seul le 5eme arg peut etre == 0 (Si les philos doivent manger 0 fois)
    if (!ft_atol(str) && n_arg != 5)//lancer ft_atol ici permet aussi de verifier qu'on depasse pas l'INT MAX
        ft_exit(INV_ARG);  
}

char **ft_parser(int ac, char **av)
{
    int i;
    
    if (ac != 5 && ac != 6)
        ft_exit(PARAM_ERROR);
    i = 0;
    while (av[++i])
        ft_checkint(av[i], i);
    //Quelle(s) limitation(s) mettre pour les autres params ?
    if (ft_atol(av[1]) < 1 || ft_atol(av[1]) > 200)//
        ft_exit(TMANY_PHILO);//
    //ASKIP 60 ms minimum pour mourrir dans la correction
    if (ac == 6 && ft_atol(av[5]) == 0)
    {
        //Si les philos ne doivent pas manger
        // write(1, "\n", 2);
        exit (0);//exit interdit !
    }
    return (av);
}
