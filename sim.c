/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:59:46 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/05 13:24:00 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//handle_i permet d'incrementer i. Si on est a la fin et que tous les philos sont full
//alors on arrete la simulation ou alors on remet i a 0 et all_full a 0. Sinon i++
//ft_next

static void     ft_next(t_philo **ptr_curr, t_data *dt, int *being_full)
{
    //Si on a atteint le dernier noeud
    if ((*ptr_curr)->next == NULL)
    {
        //On check si tous les philos sont pleins (il y a nphilo qui sont full).
        //Si c'est pas le cas on recommence
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
    usleep(100);//WHY ??
}

void *ft_monitor(void *arg)
{
    t_data          *dt;
    struct timeval  time;
    t_philo         *curr;
    int             being_full;

    dt = (t_data *)arg;
    being_full = 0;
    //Le monitor met a jour les last_meal de tous les philos
    gettimeofday(&time, NULL);
    dt->start_time = ft_time(time);
    curr = dt->philos;
    while (curr)
    {
        // if (dt->many_eat >= 0)
        //     curr->nb_meal = 0;// curr->is_full = 0;//Chaque philo va indiquer quand il est full
        curr->last_meal = ft_time(time);
        // printf("%lu\n", ft_time(time));
        curr = curr->next;
        
    }
    //Le monitor lance la simulation
    ft_setint(&dt->mut_start, &dt->start, 1);

    ft_sleep(50);//Atteindre un peu avant de checker
    
    curr = dt->philos;
    // printf("haha\n");
    while (ft_getint(&dt->mut_start, &dt->start))
    {
        // printf("haha2\n");
        // printf("%d\n", curr->id);
        
        gettimeofday(&time, NULL);
        if (ft_time(time) - ft_getlong(&dt->mut_lastmeal,
            &curr->last_meal) > dt->t_die)
        {
            // printf("fin : %d\n", curr->id);
            // printf("time = %lu\n", ft_time(time));
            // printf("last meal = %lu\n", curr->last_meal);
            ft_write(curr, curr->id, "has died\n");
            ft_setint(&dt->mut_start, &dt->start, 0);
        }
        if (dt->many_eat != -1 && ft_getlong(&dt->mut_nbmeal,
            &curr->nb_meal) > dt->many_eat)
            being_full++;
        ft_next(&curr, dt, &being_full);//A CODER
    }


    
    
    ////////////////////////////////
    //Le monitor compare l'heure actuelle avec l'heure a laquelle il a mange pour la derniere fois (last_meal est dans dt)
    //et si le monitor constate que la deadline est depassee alors il met une dummy a 1 dans dt, et tous les threads ayant
    //acces a cette dummy s'arretent.
    // ft_sleep(1000);
    // ft_setint(&dt->mut_start, &dt->start, 0);
    //Checker le temps que prend chaque philo en permanence
    return (NULL);
}

// printf("(start %d)Thread [%d] a pris 1 fourchette. (f_fork: %p, s_fork: %p)\n", ft_getint(&philo->dt->mut_start, &philo->dt->start),
        // philo->id, (void *)philo->f_fork, (void *)philo->s_fork);
void *ft_philos(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    struct timeval	time;
    // printf("coucou\n");
    // if (philo->dt->nphilo == 1)
    // {
    //     printf("coucou2\n");
    //     ft_write(philo, philo->id, "has taken a fork\n");
    //     return (NULL);
    // }
    while (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
        ft_sleep(1);
    if (philo->dt->nphilo == 1)
    {
        // printf("coucou2\n");
        ft_write(philo, philo->id, "has taken a fork\n");
        return (NULL);
    }
    if (philo->id % 2 != 0)
        ft_sleep(30);

    while (ft_getint(&philo->dt->mut_start, &philo->dt->start))
    {
        pthread_mutex_lock(philo->f_fork);
        ft_write(philo, philo->id, "has taken a fork\n");
        pthread_mutex_lock(philo->s_fork);
        ft_write(philo, philo->id, "has taken a fork\n");
        // pthread_mutex_lock(philo->f_fork);
        // ft_write(philo, philo->id, "has taken a fork\n");
        gettimeofday(&time, NULL);
        ft_setlong(&philo->dt->mut_lastmeal, &philo->last_meal, ft_time(time));
        ft_write(philo, philo->id, "is eating\n");
        ft_sleep(philo->dt->t_eat);
        pthread_mutex_lock(&philo->dt->mut_nbmeal);
        philo->nb_meal = philo->nb_meal + 1;
        pthread_mutex_unlock(&philo->dt->mut_nbmeal);
        pthread_mutex_unlock(philo->f_fork);
        pthread_mutex_unlock(philo->s_fork);

        ft_write(philo, philo->id, "is sleeping\n");
        ft_sleep(philo->dt->t_sleep);//Pas besoin de le proteger ?

        ft_write(philo, philo->id, "is thinking\n");
        ft_think(philo->dt);
    }
    return (NULL);
}