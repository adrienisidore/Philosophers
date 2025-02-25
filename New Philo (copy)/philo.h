/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:41:00 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/25 16:31:38 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>//printf (useless en temps normal)
# include <unistd.h>//write
# include <stdlib.h>//exit, size_t
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
    pthread_t       thread;
    pthread_mutex_t *mutex;
    struct s_philo* next;
}   t_philo;

#endif