/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:57:52 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/05 18:34:26 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time(struct timeval time)
{
	long	res;

	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}

void	ft_sleep(long usec)
{
	struct timeval	time;
	long			curr_time;
	long			begin;

	gettimeofday(&time, NULL);
	begin = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (1)
	{
		gettimeofday(&time, NULL);
		curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
		if (curr_time - begin < usec)
			usleep(500);
		else
			break ;
	}
}

void	ft_think(t_data *dt)
{
	long	time;

	if (dt->nphilo % 2 == 0)
		return ;
	time = dt->t_eat * 2 - dt->t_sleep;
	if (time < 0)
		time = 0;
	ft_sleep(time);
}

static void	ft_putstr_fd(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		write(1, &str[i], 1);
}

void	ft_write(t_philo *philo, int id, char *str)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->dt->mut_stdout);
	if (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
	{
		pthread_mutex_unlock(&philo->dt->mut_stdout);
		return ;
	}
	gettimeofday(&time, NULL);
	ft_putstr_fd(ft_ltoa(ft_time(time) - ft_getlong(&philo->dt->mut_startime,
				&philo->dt->start_time)));
	ft_putstr_fd(" ");
	ft_putstr_fd(ft_ltoa((long) id));
	ft_putstr_fd(" ");
	ft_putstr_fd(str);
	pthread_mutex_unlock(&philo->dt->mut_stdout);
}
