/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:53:12 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/05 18:14:34 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Supp executable + les .o

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

int	main(int ac, char **av)
{
	t_data	*dt;
	t_philo	*curr;

	if (!ft_parser(ac, av))
		return (0);
	dt = ft_inidt(ac, ft_parser(ac, av));
	if (!dt || dt->forks == NULL || dt->philos == NULL)
		return(1);
	curr = dt->philos;
	while (curr)
	{
		pthread_create(&curr->thread, NULL, ft_philos, (void*)curr);
		curr = curr->next;
	}
	pthread_create(&dt->monit, NULL, ft_monitor, dt);
	pthread_join(dt->monit, NULL);
	curr = dt->philos;
	while (curr)
	{
		pthread_join(curr->thread, NULL);
		curr = curr->next;
	}
	return (ft_freeall(dt->forks, dt->philos, dt, NULL));
}
