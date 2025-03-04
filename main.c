/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:53:12 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/04 15:33:43 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Retracer raisonnement Erika du debut a la fin et ajouter les elements manquants puis tester

//1mettre au propre

//2 faire le temps

//GERER LE CAS OU 1 philo, 0 philo et ;any_meal == 0 (ils doivent pas manger);

//                  SUR ORDI LENT
//J'ai des deadlocks parfois (depuis que j'ai mis while (1)) : Un thread bloque une ressource
//et attend une autre qui est déjà prise par un autre thread.
//Aucun thread ne peut progresser car ils attendent tous indéfiniment.
//HYPOTHESES : certains threads attendent d'avoir acces a dt->start et en meme temps ont
//des fourchettes, et en meme temps ont des fourchettes ce qui empeche les autres de
//continuer.

void    ft_exit(char *to_write)
{
    if (to_write)
    {
        write(2, to_write, ft_strlen(to_write));
        //L'exit code doit il changer en fonction de ce qui pete ?
        exit(1);
    }   
    //L'exit code doit il changer en fonction de ce qui pete ?
    exit(0);
    
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