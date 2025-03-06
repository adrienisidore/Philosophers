/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:01:09 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/06 19:08:40 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(char *to_write)
{
	if (to_write)
	{
		write(2, to_write, ft_strlen(to_write));
		return (1);
	}
	return (0);
}

void	ft_destroy(t_mut *mut1, t_mut *mut2, t_mut *mut3, t_mut *mut4)
{
	if (mut1)
		pthread_mutex_destroy(mut1);
	if (mut2)
		pthread_mutex_destroy(mut2);
	if (mut3)
		pthread_mutex_destroy(mut3);
	if (mut4)
		pthread_mutex_destroy(mut4);
}

static void	ft_freephilo(t_data *dt)
{
	t_philo	*temp;
	t_philo	*curr_;

	curr_ = dt->philos;
	while (curr_)
	{
		temp = curr_;
		curr_ = curr_->next;
		free(temp);
	}
}

int	ft_freeall(t_mut *forks, t_philo *lst_philo, t_data *dt, char *str)
{
	int	k;

	k = -1;
	if (forks)
	{
		while (++k < dt->nphilo)
			pthread_mutex_destroy(&dt->forks[k]);
		free(dt->forks);
	}
	if (lst_philo)
		ft_freephilo(dt);
	if (forks && lst_philo && dt)
	{
		ft_destroy(&dt->mut_stdout, &dt->mut_start,
			&dt->mut_lastmeal, &dt->mut_nbmeal);
		pthread_mutex_destroy(&dt->mut_startime);
	}
	if (dt)
		free(dt);
	return (ft_exit(str));
}

int	ft_fail(t_data *dt, t_philo *curr)
{
	t_philo	*failed;

	failed = curr;
	curr = dt->philos;
	ft_setint(&dt->mut_fail, &dt->fail, 1);
	while (curr != failed)
	{
		pthread_join(curr->thread, NULL);
		curr = curr->next;
	}
	pthread_mutex_destroy(&dt->mut_fail);
	ft_freeall(dt->forks, dt->philos, dt, NULL);
	return (ft_exit(TH_FAIL));
}