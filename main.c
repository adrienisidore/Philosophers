/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:53:12 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/27 17:57:44 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//1mettre au propre

//2 faire le temps


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
    ///////////////////////////////////////////////// MANGER
    pthread_mutex_lock(philo->s_fork);
    pthread_mutex_lock(philo->f_fork);
    //Pour chaque philo, je regarde l'heure a laquelle il commence a manger.
    //Un monitor compare l'heure actuelle avec l'heure a laquelle il a mange pour la derniere fois (last_meal est dans dt)
    //et si le monitor constate que la deadline est depassee alors il met une dummy a 1 dans dt, et tous les threads ayant
    //acces a cette dummy s'arretent.
    pthread_mutex_lock(&philo->dt->mut_stdout);
    printf("(start %d)Thread [%d] id : %lu    dt = %p a pris 2 fourchettes et mange. (f_fork: %p, s_fork: %p)\n", philo->dt->start,
        philo->id, (unsigned long)pthread_self(), philo->dt, (void *)philo->f_fork, (void *)philo->s_fork);
    pthread_mutex_unlock(&philo->dt->mut_stdout);
    usleep(600);
    pthread_mutex_lock(&philo->dt->mut_stdout);
    printf("(start %d)Thread [%d] id : %lu    dt = %p a fini de manger. (f_fork: %p, s_fork: %p)\n", philo->dt->start,
        philo->id, (unsigned long)pthread_self(), philo->dt, (void *)philo->f_fork, (void *)philo->s_fork);
    pthread_mutex_unlock(&philo->dt->mut_stdout);
    pthread_mutex_unlock(philo->f_fork);
    pthread_mutex_unlock(philo->s_fork);
    ///////////////////////////////////////////////////////
    
    /////////////////////// DORMIR
    pthread_mutex_lock(&philo->dt->mut_stdout);
    printf("Thread [%d] id : %lu dort pendant %dms.\n",
        philo->id, (unsigned long)pthread_self(), 600);
    pthread_mutex_unlock(&philo->dt->mut_stdout);
    usleep(600);
    ///////////////////////
    // }
    
    return NULL;
}

t_mut   *ft_initforks(t_data *dt)
{
    t_mut   *forks;
    int     i;

    //l'indexage des fourchettes est bien de 0 a 199 contrairement aux philos
    forks = malloc(sizeof(t_mut) * dt->nphilo);
    if (!forks)
    {
        free(dt);
        ft_exit(MEM_FAIL);
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
            free(dt);
            ft_exit(MUT_FAIL);
        }
    }
    return (forks);
}

t_data  *ft_inidt(int ac, char **av)
{
    t_data  *dt;
    
    dt = malloc(sizeof(t_data));
    if (!dt)
        ft_exit(MEM_FAIL);
    dt->nphilo = ft_atol(av[1]);
    dt->t_die = ft_atol(av[2]);
    dt->t_eat = ft_atol(av[3]);
    dt->t_sleep = ft_atol(av[4]);
    // dt->t_think non initialise
    if (ac == 6)
        dt->many_eat = ft_atol(av[5]);
    else
        dt->many_eat = -1;
    dt->forks = ft_initforks(dt);
    //A PROTEGER
    pthread_mutex_init(&dt->mut_start, NULL);
    pthread_mutex_init(&dt->mut_stdout, NULL);
    //si le premier pete alors on arrete (apres free)
    //Si le 2eme pete alors il faut destroy le 1er puis arreter (apres free)
    dt->start = 0;
    return (dt);
}

void    ft_dispatch(t_philo *new_philo, t_data *dt, int j)
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

int main(int ac, char **av)
{
    t_data   *dt;

    dt = ft_inidt(ac, ft_parser(ac, av));

    /////////initphilos(dt) : a la fin lst est arime a dt via dt->philos;
    //L'INDICE DES PHILOS PART DE 1
    //On peut pas rassembler les 3 t_philos* dans un tableau de pointeurs ??
    
    //On initialise les philos apres dt comme ca on peut faire new_node->dt = dt;
    t_philo *lst;
    t_philo *new_philo;
    t_philo *current;
    int      j;
    
    lst = NULL;
    j = 0;
    while (++j <= dt->nphilo)
    {
        new_philo = malloc(sizeof(t_philo));
        new_philo->dt = dt;
        new_philo->id = j;
        ft_dispatch(new_philo, dt, j);
        new_philo->next = NULL;
        if (!lst)
            lst = new_philo;
        else
            current->next = new_philo;
        current = new_philo;
    }

    // dt->philos = ft_initphilos(dt);


    
    ////////////////////////////Lancement simulation
    t_philo *curr;
    
    curr = lst;
    while (curr)
    {
        pthread_create(&curr->thread, NULL, ft_philos, (void*)curr);
        curr = curr->next;
    }
    //TOUS LES THREADS SONT PRETS :
    //Le monitor met start a 1 et mesure l'heure pour savoir quand la simulation commence
    pthread_create(&dt->monit, NULL, ft_monitor, dt);
    pthread_join(dt->monit, NULL);
    curr = lst;
    while (curr)
    {
        pthread_join(curr->thread, NULL);
        curr = curr->next;
    }


    //////////////////Fin de simulation
    t_philo *temp;
    t_philo *curr_;
    int     k;
    
    k = -1;
    //RAPPEL : l'indexage des fourchettes est bien de 0 a 199
    //contrairement aux philos
    while (++k < dt->nphilo)
    {
        pthread_mutex_destroy(&dt->forks[k]);
    }
    free(dt->forks);
    
    curr_ = lst;
    while (curr_)
    {
        temp = curr_;
        curr_ = curr_->next;
        free(temp);
    }
    pthread_mutex_destroy(&dt->mut_stdout);
    pthread_mutex_destroy(&dt->mut_start);
    free(dt);
    
    return (0);
}