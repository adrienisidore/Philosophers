/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:41:00 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/27 15:04:59 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define NB_PHILO 200

# include <stdio.h>//printf (useless en temps normal)
# include <unistd.h>//write
# include <stdlib.h>//exit, size_t
# include <pthread.h>
# include <limits.h>

typedef struct s_data t_data;
typedef pthread_mutex_t	t_mut;

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    t_mut *f_fork;
    t_mut *s_fork;
    t_data          *dt;
    struct s_philo* next;
}   t_philo;

typedef struct s_data
{
    int             start;
    t_mut           *mut_start;
    t_mut           *mut_stdout;
    pthread_t       monit;
    t_philo         *philos; 
}   t_data;

void    ft_setint(t_mut *mut_, int *to_set, int value);
void    ft_setlong(t_mut *mut_, long *to_set, long value);
int     ft_getint(t_mut *mut_, int *to_get);
long    ft_getlong(t_mut *mut_, long *to_get);

#endif