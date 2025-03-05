/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:57:52 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/05 13:31:37 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Pourrait etre static non ? Si oui retirer proto .h
long    ft_time(struct timeval time)
{
	long	res;

	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}

//static ? Si non ajouter proto dans .h
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
			usleep(500);//WHY ?? Demander a Paul
		else
			break ;
	}
}

//SAVOIR EXPLIQUER
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
	struct timeval	time;//On en a besoin pour recuperer la valeur de last_meal

	(void)id;
	(void)str;
	pthread_mutex_lock(&philo->dt->mut_stdout);
	if (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
	{
		// printf("ecrit pas\n");
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
	//Erika utilise un flag pour arreter d'ecrire
	pthread_mutex_unlock(&philo->dt->mut_stdout);

}