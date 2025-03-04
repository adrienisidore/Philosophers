/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inidt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:57:39 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/04 15:32:24 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_mut   *ft_initforks(t_data *dt)
{
    t_mut   *forks;
    int     i;

    //l'indexage des fourchettes est bien de 0 a 199 contrairement aux philos
    forks = malloc(sizeof(t_mut) * dt->nphilo);
    if (!forks)
    {
        ft_destroy(&dt->mut_stdout, &dt->mut_start,
            &dt->mut_lastmeal, &dt->mut_nbmeal);
        ft_freeall(NULL, NULL, dt, MEM_FAIL);   
    }
    i = -1;
    while (++i < dt->nphilo)
    {
        //Chaque fourchette est un mutex et seul le tableau est * (malloce) donc on fait
        //la meme chose pour mut_stdout et mut_start (ils deviennent juste des mutex)
        // pthread_mutex_init(&forks[i], NULL);
        if (pthread_mutex_init(&forks[i], NULL))
        {
            while (--i >= 0)
                pthread_mutex_destroy(&forks[i]);
            free(forks);
            ft_destroy(&dt->mut_stdout, &dt->mut_start,
                &dt->mut_lastmeal, &dt->mut_nbmeal);
            pthread_mutex_destroy(&dt->mut_startime);
            ft_freeall(NULL, NULL, dt, MUT_FAIL);
        }
    }
    return (forks);
}

static void    ft_dispatch(t_philo *new_philo, t_data *dt, int j)
{
    if (new_philo->id % 2 == 0)
    {
        new_philo->f_fork = &dt->forks[j - 1];
        new_philo->s_fork = &dt->forks[j % dt->nphilo];
    }   
    else
    {
        new_philo->s_fork = &dt->forks[j - 1];
        new_philo->f_fork = &dt->forks[j % dt->nphilo];
    }
}

static t_philo  *ft_initphilo(t_data *dt)
{
    t_philo *lst;
    t_philo *new_philo;
    t_philo *current;
    int      j;
    
    lst = NULL;
    j = 0;
    while (++j <= dt->nphilo)
    {
        new_philo = malloc(sizeof(t_philo));
        if (!new_philo)
            ft_freeall(dt->forks, dt->philos, dt, MEM_FAIL);
        new_philo->dt = dt;
        new_philo->nb_meal = dt->many_eat;
        new_philo->id = j;
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

static void ft_initmutex(t_data *dt)
{
    if (pthread_mutex_init(&dt->mut_start, NULL))
        ft_freeall(NULL, NULL, dt, MUT_FAIL);
    if (pthread_mutex_init(&dt->mut_stdout, NULL))
    {
        pthread_mutex_destroy(&dt->mut_start);
        ft_freeall(NULL, NULL, dt, MUT_FAIL); 
    }
    if (pthread_mutex_init(&dt->mut_lastmeal, NULL))
    {
        ft_destroy(&dt->mut_stdout, &dt->mut_start, NULL, NULL);
        ft_freeall(NULL, NULL, dt, MUT_FAIL); 
    }
    if (pthread_mutex_init(&dt->mut_nbmeal, NULL))
    {
        ft_destroy(&dt->mut_stdout, &dt->mut_start,
            &dt->mut_lastmeal, NULL);
        ft_freeall(NULL, NULL, dt, MUT_FAIL); 
    }
    if (pthread_mutex_init(&dt->mut_startime, NULL))
    {
        ft_destroy(&dt->mut_stdout, &dt->mut_start,
            &dt->mut_lastmeal, &dt->mut_nbmeal);
        ft_freeall(NULL, NULL, dt, MUT_FAIL); 
    }
}

t_data  *ft_inidt(int ac, char **av)
{
    t_data          *dt;
    
    dt = malloc(sizeof(t_data));
    if (!dt)
        ft_exit(MEM_FAIL);
    ft_initmutex(dt);
    dt->nphilo = ft_atol(av[1]);
    dt->t_die = ft_atol(av[2]);
    dt->t_eat = ft_atol(av[3]);
    dt->t_sleep = ft_atol(av[4]);
    dt->start = 0;
    if (ac == 6)
        dt->many_eat = ft_atol(av[5]);
    else
        dt->many_eat = -1;
    dt->forks = ft_initforks(dt);
    dt->philos = ft_initphilo(dt);
    return (dt);
}