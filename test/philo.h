/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:41:00 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/19 14:57:09 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>//printf (useless en temps normal)
# include <unistd.h>//write
# include <stdlib.h>//exit, size_t
# include <pthread.h>
# include <limits.h>

# define R_SYNTAX        "philo: Correct syntax: ./philo number_of_philosophers time_to_die "
# define PARAM_ERROR     R_SYNTAX "time_to_eat time_to_sleep" PARAM_OPT
# define PARAM_OPT       " [number_of_times_each_philosopher_must_eat]\n"
# define INV_ARG         "philo: Invalid argument(s)" INV_ARG_MORE
# define INV_ARG_MORE    ", enter valid arguments between 1 and 2 147 483 647ms\n"
# define TMANY_PHILO     "philo: number_of_philosophers must be between 1 and 200\n"

typedef struct s_data t_data;

//un noeud par philo
typedef struct s_philo
{
    int             idx;
    pthread_t		thread;
    pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
    t_data          *dt;
    //ptr vers les mutex 
}   t_philo;

//structure data recupere av + pointeur vers liste chainee des philos
typedef struct s_data
{
    int     t_die;
    int     t_eat;
    int     t_sleep;
    int     t_think;
    int     many_eat;
    t_philo *philos;
}   t_data;

//fourchettes = mutex : 2 necessaires pour manger

//t_think est a creer pour occuper les paires/impairs qui ont mange trop vite (t_eat + t_sleep - t_die) / n
//pour creer un decalage. Quand philo a fini de dormir, au lieu de choper une fourchette il attend que son groupe ai fini.
//Toutes les variables "mutex" (comme les fourchettes, la variable write, dead) sont a init et a lock/unlock

//1 philo = 1 thread qui fait des actions => 1 idx, et des pointeurs vers les mutex de la structure generale
//1 boucle infini qui va lancer tous les thread et les exec, jusqu'a ce que 1 meurt

//main.c
void        ft_error(char *to_write);

//parsing.c
void        ft_parser(int ac, char **av);

//utils.c
size_t	    ft_strlen(const char *str);
int         ft_isnum(const char c);
int         ft_ispace(const char c);
long int	ft_atol(const char *str);

#endif