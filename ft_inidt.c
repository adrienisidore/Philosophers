/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inidt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:57:39 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/06 16:53:53 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_mut	*ft_mallocforks(t_data *dt)
{
	t_mut	*forks;

	forks = malloc(sizeof(t_mut) * dt->nphilo);
	if (!forks)
	{
		ft_destroy(&dt->mut_stdout, &dt->mut_start,
			&dt->mut_lastmeal, &dt->mut_nbmeal);
		pthread_mutex_destroy(&dt->mut_fail);
		ft_freeall(NULL, NULL, dt, MEM_FAIL);
		return (NULL);
	}
	return (forks);
}

static t_mut	*ft_initforks(t_data *dt)
{
	t_mut	*forks;
	int		i;

	forks = ft_mallocforks(dt);
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < dt->nphilo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			ft_destroy(&dt->mut_stdout, &dt->mut_start,
				&dt->mut_lastmeal, &dt->mut_nbmeal);
			ft_destroy(&dt->mut_startime, &dt->mut_fail, NULL, NULL);
			ft_freeall(NULL, NULL, dt, MUT_FAIL);
			return (NULL);
		}
	}
	return (forks);
}

static t_philo	*ft_initphilo(t_data *dt)
{
	t_philo	*lst;
	t_philo	*new_philo;
	t_philo	*current;
	int		j;

	lst = NULL;
	j = 0;
	while (++j <= dt->nphilo)
	{
		new_philo = malloc(sizeof(t_philo));
		if (!new_philo)
		{
			pthread_mutex_destroy(&dt->mut_fail);
			ft_freeall(dt->forks, dt->philos, dt, MEM_FAIL);
			return (NULL);
		}
		ft_dispatch(new_philo, dt, j);
		new_philo->next = NULL;
		if (!lst)
			lst = new_philo;
		else
			current->next = new_philo;
		current = new_philo;
	}
	return (lst);
}

static int	ft_initmutex(t_data *dt)
{
	if (pthread_mutex_init(&dt->mut_start, NULL))
		return (ft_freeall(NULL, NULL, dt, MUT_FAIL));
	if (pthread_mutex_init(&dt->mut_stdout, NULL))
	{
		pthread_mutex_destroy(&dt->mut_start);
		return (ft_freeall(NULL, NULL, dt, MUT_FAIL));
	}
	if (pthread_mutex_init(&dt->mut_lastmeal, NULL))
	{
		ft_destroy(&dt->mut_stdout, &dt->mut_start, NULL, NULL);
		return (ft_freeall(NULL, NULL, dt, MUT_FAIL));
	}
	if (pthread_mutex_init(&dt->mut_nbmeal, NULL))
	{
		ft_destroy(&dt->mut_stdout, &dt->mut_start,
			&dt->mut_lastmeal, NULL);
		return (ft_freeall(NULL, NULL, dt, MUT_FAIL));
	}
	if (pthread_mutex_init(&dt->mut_startime, NULL))
	{
		ft_destroy(&dt->mut_stdout, &dt->mut_start,
			&dt->mut_lastmeal, &dt->mut_nbmeal);
		return (ft_freeall(NULL, NULL, dt, MUT_FAIL));
	}
	return (0);
}

t_data	*ft_inidt(int ac, char **av)
{
	t_data	*dt;

	dt = malloc(sizeof(t_data));
	if (!dt)
	{
		ft_exit(MEM_FAIL);
		return (NULL);
	}
	if (pthread_mutex_init(&dt->mut_fail, NULL))
	{
		ft_freeall(NULL, NULL, dt, MUT_FAIL);
		return (NULL);
	}
	if (ft_initmutex(dt))
		return (NULL);
	ft_stackdt(dt, av);
	if (ac == 6)
		dt->many_eat = ft_atol(av[5]);
	else
		dt->many_eat = -1;
	dt->forks = ft_initforks(dt);
	dt->philos = ft_initphilo(dt);
	return (dt);
}
