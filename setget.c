/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setget.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:52:55 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/06 18:06:49 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_setint(t_mut *mut_, int *to_set, int value)
{
	pthread_mutex_lock(mut_);
	*to_set = value;
	pthread_mutex_unlock(mut_);
}

void	ft_setlong(t_mut *mut_, long *to_set, long value)
{
	pthread_mutex_lock(mut_);
	*to_set = value;
	pthread_mutex_unlock(mut_);
}

int	ft_getint(t_mut *mut_, int *to_get)
{
	int	res;

	pthread_mutex_lock(mut_);
	res = *to_get;
	pthread_mutex_unlock(mut_);
	return (res);
}

long	ft_getlong(t_mut *mut_, long *to_get)
{
	long	res;

	pthread_mutex_lock(mut_);
	res = *to_get;
	pthread_mutex_unlock(mut_);
	return (res);
}
