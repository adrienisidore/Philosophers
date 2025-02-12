/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:41:00 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/12 12:52:30 by aisidore         ###   ########.fr       */
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

//un noeud par philo
typedef struct s_philo
{
    int     idx;
    //ptr vers les mutex 
}   t_philo;

//structure data recupere av + pointeur vers liste chainee des philos
typedef struct s_data
{
    int     idx;
    size_t  t_die;
    size_t  t_eat;
    size_t  t_sleep;
    size_t  t_think;
    size_t  many_eat;
    t_philo philos;
}   t_data;

//fourchettes = mutex : 2 necessaires pour manger

//t_think est a creer pour occuper les paires/impairs qui ont mange trop vite (t_eat + t_sleep - t_die) / n
//pour creer un decalage. Quand philo a fini de dormir, au lieu de choper une fourchette il attend que son groupe ai fini.
//Toutes les variables "mutex" (comme les fourchettes, la variable write, dead) sont a init et a lock/unlock

//1 philo = 1 thread qui fait des actions => 1 idx, et des pointeurs vers les mutex de la structure generale
//1 boucle infini qui va lancer tous les thread et les exec, jusqu'a ce que 1 meurt


//error.c
void ft_parser(int ac, char **av);

//utils.c
size_t	ft_strlen(const char *str);
int     ft_atoi(const char *str);
int     ft_isnum(const char c);
int     ft_ispace(const char c);

#endif