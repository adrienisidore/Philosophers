/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:53:12 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/05 16:14:47 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//chmod 777 test.sh (dans le repo thales ?)
//NE PASCOMPILER AVEC SANITIZE
//./test.sh ../Philosophers/ 1

//Retracer raisonnement Erika du debut a la fin et ajouter les elements manquants puis tester

//1finir ft_write

//implementer tout le reste



int    ft_exit(char *to_write)
{
    if (to_write)
    {
        write(2, to_write, ft_strlen(to_write));
		exit(1);
		return (1);
    }
	exit(0);
	return (0);   
}

void   ft_destroy(t_mut *mut1, t_mut *mut2, t_mut *mut3, t_mut *mut4)
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

static void    ft_freephilo(t_data *dt)
{
    t_philo *temp;
    t_philo *curr_;
    
    curr_ = dt->philos;
    while (curr_)
    {
        temp = curr_;
        curr_ = curr_->next;
        free(temp);
    }
}

int    ft_freeall(t_mut *forks, t_philo *lst_philo, t_data *dt, char *str)
{
    int     k;
    
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
    ft_exit(str);
    return (0);
}

int main(int ac, char **av)
{
	t_data   *dt;
	t_philo *curr;

	if (!ft_parser(ac, av))
		return (0);
	dt = ft_inidt(ac, ft_parser(ac, av));
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