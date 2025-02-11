/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:41:00 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/11 12:24:38 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>//printf (useless en temps normal)
# include <unistd.h>//write
# include <stdlib.h>//exit, size_t
# include <pthread.h>

# define R_SYNTAX        "Correct syntax: ./philo number_of_philosophers time_to_die "
# define INV_ARG         "Invalid argument(s): "
# define PARAM_ERROR     R_SYNTAX "time_to_eat time_to_sleep" PARAM_OPT
# define PARAM_OPT       " [number_of_times_each_philosopher_must_eat]\n"
# define LARGE_PARAM     INV_ARG "No argument can exceed XXX miliseconds\n"
# define FORBID_PARAM    INV_ARG "positive numbers required\n"
# define TMANY_PHILO     INV_ARG "number_of_philosophers must be between 1 and 200\n"

typedef struct s_philo
{
    int     idx;
    size_t  t_die;
    size_t  t_eat;
    size_t  t_sleep;
    size_t  t_think;
}   t_philo;

//error.c
void ft_parser(int ac, char **av);

//utils.c
size_t	ft_strlen(const char *str);
int     ft_atoi(const char *str);
int     ft_isnum(const char c);
int     ft_ispace(const char c);

#endif