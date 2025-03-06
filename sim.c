/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:59:46 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/06 15:47:41 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// usleep(10);//decharger CPU

#include "philo.h"

static void	ft_next(t_philo **ptr_curr, t_data *dt, int *being_full)
{
	if ((*ptr_curr)->next == NULL)
	{
		if (*being_full == dt->nphilo)
			ft_setint(&dt->mut_start, &dt->start, 0);
		else
		{
			*ptr_curr = dt->philos;
			*being_full = 0;
		}
	}
	else
		*ptr_curr = (*ptr_curr)->next;
	usleep(100);//Reduit puissance CPU et permet a certains de manger assez de fois
}

static void	ft_check(t_data *dt, t_philo *curr, int *being_full)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	// printf("since begin : %lu philo[%d] last meal : %lu\n", ft_time(time) - ft_getlong(&dt->mut_startime, &dt->start_time), curr->id, ft_time(time) - ft_getlong(&dt->mut_lastmeal, &curr->last_meal));
	if (ft_time(time) - ft_getlong(&dt->mut_lastmeal,
		&curr->last_meal) > dt->t_die)
	{
		// printf("since begin ; %lu", ft_time(time) - ft_getlong(&dt->mut_startime, &dt->start_time));
		ft_write(curr, curr->id, "died\n");
		ft_setint(&dt->mut_start, &dt->start, 0);
	}
	if (dt->many_eat != -1 && ft_getlong(&dt->mut_nbmeal,
		&curr->nb_meal) > dt->many_eat)
		(*being_full)++;
}

void *ft_monitor(void *arg)
{
	t_data			*dt;
	struct timeval	time;
	t_philo			*curr;
	int				being_full;

	dt = (t_data *)arg;
	being_full = 0;
	gettimeofday(&time, NULL);
	dt->start_time = ft_time(time);
	curr = dt->philos;
	while (curr)
	{
		curr->last_meal = ft_time(time);
		curr = curr->next;
	}
	ft_setint(&dt->mut_start, &dt->start, 1);
	ft_sleep(50, dt);
	curr = dt->philos;
	while (ft_getint(&dt->mut_start, &dt->start))
	{
		ft_check(dt, curr, &being_full);
		ft_next(&curr, dt, &being_full);
	}
	return (NULL);
}

static void	ft_eat(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(philo->f_fork);
	ft_write(philo, philo->id, "has taken a fork\n");
	pthread_mutex_lock(philo->s_fork);
	ft_write(philo, philo->id, "has taken a fork\n");
	gettimeofday(&time, NULL);
	ft_setlong(&philo->dt->mut_lastmeal, &philo->last_meal, ft_time(time));
	ft_write(philo, philo->id, "is eating\n");
	ft_sleep(philo->dt->t_eat, philo->dt);
	pthread_mutex_lock(&philo->dt->mut_nbmeal);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->dt->mut_nbmeal);
	pthread_mutex_unlock(philo->f_fork);
	pthread_mutex_unlock(philo->s_fork);
}

void	*ft_philos(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
		usleep(20);//&& pas de probleme. Si pb alors on arrete return (NULL);
	if (philo->dt->nphilo == 1)
	{
		ft_write(philo, philo->id, "has taken a fork\n");
		return (NULL);
	}
	if (philo->id % 2 != 0)
		ft_sleep(30, philo->dt);
	while (ft_getint(&philo->dt->mut_start, &philo->dt->start))
	{
		ft_eat(philo);
		ft_write(philo, philo->id, "is sleeping\n");
		ft_sleep(philo->dt->t_sleep, philo->dt);
		ft_write(philo, philo->id, "is thinking\n");
		ft_think(philo->dt);
	}
	return (NULL);
}
