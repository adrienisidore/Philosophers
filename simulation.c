/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:59:46 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/03 14:01:07 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ft_monitor(void *arg)
{
    t_data          *dt;

    dt = (t_data *)arg;
    //Le temps que tous les autres threads aient ete cree
    pthread_mutex_lock(&dt->mut_stdout);
    printf("Monitor start ...\n");
    pthread_mutex_unlock(&dt->mut_stdout);
    //Le monitor est cree apres les philos, ils attendent l'avale du monitor pour commencer...
    ft_setint(&dt->mut_start, &dt->start, 1);
    pthread_mutex_lock(&dt->mut_stdout);
    printf("Tous les threads sont prets, lancement de la simulation ...\n");
    pthread_mutex_unlock(&dt->mut_stdout);
    //A la place du usleep on check si un philo a pris trop de temps
    //entre son last meal et quand il commence a manger
    usleep(10000);
    ft_setint(&dt->mut_start, &dt->start, 0);
    //Checker le temps que prend chaque philo en permanence
    return (NULL);
}

void *ft_philos(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // Les threads impairs attendent un peu pour éviter la compétition immédiate
    //USELESS ? askip non pour un grand nb de mutex et sur les machines lentes

    //Tant que la dummy start (protege par un mutex) est a 0 on attend 10 millisecondes
    while (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
        usleep(5);
    if (philo->id % 2 != 0)
        usleep(20);
    
    while (1)
    {
        ///////////////////////////////////////////////// MANGER
        pthread_mutex_lock(philo->s_fork);
        pthread_mutex_lock(philo->f_fork);
        if (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
        {
            pthread_mutex_unlock(philo->f_fork);
            pthread_mutex_unlock(philo->s_fork);
            return (NULL);
        }
        //Pour chaque philo, je regarde l'heure a laquelle il commence a manger.
        //Un monitor compare l'heure actuelle avec l'heure a laquelle il a mange pour la derniere fois (last_meal est dans dt)
        //et si le monitor constate que la deadline est depassee alors il met une dummy a 1 dans dt, et tous les threads ayant
        //acces a cette dummy s'arretent.
        pthread_mutex_lock(&philo->dt->mut_stdout);
        printf("(start %d)Thread [%d] id : %lu    dt = %p a pris 2 fourchettes et mange. (f_fork: %p, s_fork: %p)\n", ft_getint(&philo->dt->mut_start, &philo->dt->start),
            philo->id, (unsigned long)pthread_self(), philo->dt, (void *)philo->f_fork, (void *)philo->s_fork);
        pthread_mutex_unlock(&philo->dt->mut_stdout);
        usleep(600);
        if (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
        {
            pthread_mutex_unlock(philo->f_fork);
            pthread_mutex_unlock(philo->s_fork);
            return (NULL);
        }
        pthread_mutex_unlock(philo->f_fork);
        pthread_mutex_unlock(philo->s_fork);
        if (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
            return (NULL);
        pthread_mutex_lock(&philo->dt->mut_stdout);
        printf("(start %d)Thread [%d] id : %lu    dt = %p a fini de manger. (f_fork: %p, s_fork: %p)\n", ft_getint(&philo->dt->mut_start, &philo->dt->start),
            philo->id, (unsigned long)pthread_self(), philo->dt, (void *)philo->f_fork, (void *)philo->s_fork);
        pthread_mutex_unlock(&philo->dt->mut_stdout);
        ///////////////////////////////////////////////////////
        if (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
            return (NULL);
        /////////////////////// DORMIR
        pthread_mutex_lock(&philo->dt->mut_stdout);
        printf("Thread [%d] id : %lu dort pendant %dms.\n",
            philo->id, (unsigned long)pthread_self(), 600);
        pthread_mutex_unlock(&philo->dt->mut_stdout);
        usleep(600);
        if (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
            return (NULL);
        ///////////////////////
    }

    return (NULL);
}