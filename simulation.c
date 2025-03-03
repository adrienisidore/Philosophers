/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:59:46 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/03 17:34:48 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ft_monitor(void *arg)
{
    t_data          *dt;
    struct timeval  time;
    t_philo         *curr;

    dt = (t_data *)arg;
    //Le monitor met a jour les last_meal de tous les philos
    gettimeofday(&time, NULL);
    curr = dt->philos;
    while (curr)
    {
        if (dt->many_eat >= 0)
            curr->is_full = 0;//Chaque philo va indiquer quand il est full
        curr->last_meal = ft_time(time);
        curr = curr->next;
    }
    //Le monitor lance la simulation
    ft_setint(&dt->mut_start, &dt->start, 1);
    
    ////////////////////////////////
    //Le monitor compare l'heure actuelle avec l'heure a laquelle il a mange pour la derniere fois (last_meal est dans dt)
    //et si le monitor constate que la deadline est depassee alors il met une dummy a 1 dans dt, et tous les threads ayant
    //acces a cette dummy s'arretent.
    usleep(10000);
    ft_setint(&dt->mut_start, &dt->start, 0);
    //Checker le temps que prend chaque philo en permanence
    return (NULL);
}

//FOR LATER
// static void	ft_putstr_fd(char *str)
// {
// 	int	i;

// 	i = -1;
// 	if (!str)
// 		return ;
// 	while (str[++i])
// 		write(1, &str[i], 1);
// }

static int	ft_write(t_philo *philo, int id, char *s)
{
	struct timeval	time;//On en a besoin pour recuperer la valeur de last_meal
	long			curr_time;

    (void)s;
    (void)id;
	pthread_mutex_lock(&philo->dt->mut_stdout);
    if (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
    {
        pthread_mutex_unlock(philo->f_fork);
        pthread_mutex_unlock(philo->s_fork);
        pthread_mutex_unlock(&philo->dt->mut_stdout);
        return (0);   
    }
    gettimeofday(&time, NULL);
    curr_time = ft_getlong(&philo->dt->l_meal, &philo->last_meal);
    //AVEC ft_putstr_fd :
    //ft_putstr_fd(ft_ltoa(current - long_get(&philo->table->time,
				// &philo->table->start_time)));
    pthread_mutex_unlock(&philo->dt->mut_stdout);
    return (1);

}

void *ft_philos(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    struct timeval	time;

    while (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
        usleep(5);
    if (philo->id % 2 != 0)
        usleep(20);
    
    while (1)
    {
        pthread_mutex_lock(philo->s_fork);
        //A pris une fourchette
        pthread_mutex_lock(philo->f_fork);
        //A pris une fourchette
        gettimeofday(&time, NULL);
        ft_setlong(&philo->dt->l_meal, &philo->last_meal, ft_time(time));
        //UNUSED ARGUMENTS
        if (!ft_write(philo, 0, NULL))
            return (NULL);
        pthread_mutex_unlock(philo->f_fork);
        pthread_mutex_unlock(philo->s_fork);

        ///////////////////////////////////////////////////////
        if (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
            return (NULL);
        /////////////////////// DORMIR
        pthread_mutex_lock(&philo->dt->mut_stdout);
        printf("Thread [%d] id : %lu dort pendant %dms.\n",
            philo->id, (unsigned long)pthread_self(), 600);
        pthread_mutex_unlock(&philo->dt->mut_stdout);
        usleep(6000);
        if (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
            return (NULL);
        ///////////////////////
    }
    return (NULL);
}