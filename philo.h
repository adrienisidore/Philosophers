/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:41:00 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/04 15:30:15 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define R_SYNTAX        "philo: Correct syntax: ./philo number_of_philosophers time_to_die "
# define PARAM_ERROR     R_SYNTAX "time_to_eat time_to_sleep" PARAM_OPT
# define PARAM_OPT       " [number_of_times_each_philosopher_must_eat]\n"
# define INV_ARG         "philo: Invalid argument(s)" INV_ARG_MORE
# define INV_ARG_MORE    ", enter valid arguments between 1 and 2 147 483 647ms\n"
# define TMANY_PHILO     "philo: number_of_philosophers must be between 1 and 200\n"
# define MEM_FAIL        "philo: Memory allocation failed\n"
# define MUT_FAIL        "philo: Mutex initialisation failed\n"
# define TH_FAIL         "philo: Thread creation failed\n"
# define THC_FAIL        "philo: Thread connexion failed\n"

# include <stdio.h>//printf (useless en temps normal), essayer de l'enlever a la fin pour voir
# include <unistd.h>//write
# include <stdlib.h>//exit, size_t
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data t_data;
typedef pthread_mutex_t	t_mut;

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    t_mut           *f_fork;
    t_mut           *s_fork;
    long			last_meal;//heure du dernier repas
    long			nb_meal;
    int             is_full;
    t_data          *dt;
    struct s_philo* next;
}   t_philo;

typedef struct s_data
{
    int             start;
    long            start_time;
    long            nphilo;
    long            t_die;
    long            t_eat;
    long            t_sleep;
    long            many_eat;
    t_mut           mut_start;
    t_mut           mut_stdout;
    t_mut           *forks;
    t_mut           mut_lastmeal;
    t_mut           mut_nbmeal;
    t_mut           mut_startime;
    pthread_t       monit;
    t_philo         *philos; 
}   t_data;

//main.c
void        ft_exit(char *to_write);
void        ft_destroy(t_mut *mut1, t_mut *mut2, t_mut *mut3, t_mut *mut4);
int         ft_freeall(t_mut *forks, t_philo *lst_philo, t_data *dt, char *str);

//ft_parser.c
char        **ft_parser(int ac, char **av);

//utils.c
size_t	    ft_strlen(const char *str);
long int	ft_atol(const char *str);
char	    *ft_ltoa(long n);

//ft_setget.c
void        ft_setint(t_mut *mut_, int *to_set, int value);
void        ft_setlong(t_mut *mut_, long *to_set, long value);
int         ft_getint(t_mut *mut_, int *to_get);
long        ft_getlong(t_mut *mut_, long *to_get);

//ft_inidt.c
t_data      *ft_inidt(int ac, char **av);

//simulation.c
long        ft_time(struct timeval time);
void        *ft_monitor(void *arg);
void        *ft_philos(void *arg);


#endif