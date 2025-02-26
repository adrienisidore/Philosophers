/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:41:00 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/26 17:05:33 by aisidore         ###   ########.fr       */
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

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    pthread_mutex_t *f_fork;
    pthread_mutex_t *s_fork;
    t_data          *dt;
    struct s_philo* next;
}   t_philo;

typedef struct s_data
{
    int             start;
    pthread_mutex_t *mut_start;
    pthread_mutex_t *mut_stdout;
    t_philo         *philos; 
}   t_data;

#endif