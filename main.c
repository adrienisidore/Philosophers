/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:53:12 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/26 17:13:03 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mail = 0;

pthread_t       monitor;

// t_philo* ft_create_threads(pthread_mutex_t* mutex)
// {
//     t_philo* new_node;
    
//     new_node = (t_philo*)malloc(sizeof(t_philo));
//     new_node->mutex = mutex;
//     new_node->next = NULL;
//     return (new_node);
// }

//Changer une valeur protegee
void    bool_set(pthread_mutex_t *mut_, int *to_set, int value)
{
    pthread_mutex_lock(mut_);
    *to_set = value;
    pthread_mutex_unlock(mut_);
}

int    bool_send(pthread_mutex_t *mut_, int *to_get)
{
    int    res;

    pthread_mutex_lock(mut_);
    res = *to_get;//En passant par l'adresse je m'assure que le mutex protege,
    //Si je mets qu'une copie alors le mutex ne protege pas
    pthread_mutex_unlock(mut_);
    return (res);
}

void *thread_monitor(void *arg)
{
    t_data          *dt;

    dt = (t_data *)arg;
    //Le temps que tous les autres threads aient ete cree
    pthread_mutex_lock(dt->mut_stdout);
    printf("Monitor start ...\n");
    pthread_mutex_unlock(dt->mut_stdout);
    //Le monitor est cree apres les philos, ils attendent l'avale du monitor pour commencer
    bool_set(dt->mut_start, &dt->start, 1);
    pthread_mutex_lock(dt->mut_stdout);
    printf("Threads crees start = %d, lancement de la simulation ...\n", dt->start);
    pthread_mutex_unlock(dt->mut_stdout);
    return (NULL);
}

void *thread_function(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // Les threads impairs attendent un peu pour éviter la compétition immédiate
    //USELESS ? askip non pour un grand nb de mutex et sur les machines lentes

    //Tant que la dummy start (protege par un mutex) est a 0 on attend 10 millisecondes
    while (!bool_send(philo->dt->mut_start, &philo->dt->start))
    {
        // pthread_mutex_lock(&mutex);
        // printf("Thread[%d] attend...\n", philo->id);
        // pthread_mutex_unlock(&mutex);
        usleep(25);
    }
    if (philo->id % 2 != 0)
        usleep(300);  
    // pthread_mutex_lock(&mutex);
    // if (philo->id == NB_PHILO - 1)
    // {
    //     printf("Le dernier philo est lance...\n");
    //     mail++;//Seul le dernier thread incremente mail   
    // }
    // pthread_mutex_unlock(&mutex);
    // while (1)
    // {
    ///////////////////////////////////////////////// MANGER
    pthread_mutex_lock(philo->s_fork);
    pthread_mutex_lock(philo->f_fork);
    //Pour chaque philo, je regarde l'heure a laquelle il commence a manger.
    //Un monitor compare l'heure actuelle avec l'heure a laquelle il a mange pour la derniere fois (last_meal est dans dt)
    //et si le monitor constate que la deadline est depassee alors il met une dummy a 1 dans dt, et tous les threads ayant
    //acces a cette dummy s'arretent.
    pthread_mutex_lock(philo->dt->mut_stdout);
    printf("(start %d)Thread [%d] id : %lu    dt = %p a pris 2 fourchettes et mange. (f_fork: %p, s_fork: %p)\n", philo->dt->start,
        philo->id, (unsigned long)pthread_self(), philo->dt, (void *)philo->f_fork, (void *)philo->s_fork);
    pthread_mutex_unlock(philo->dt->mut_stdout);
    usleep(600);
    pthread_mutex_lock(philo->dt->mut_stdout);
    printf("(start %d)Thread [%d] id : %lu    dt = %p a fini de manger. (f_fork: %p, s_fork: %p)\n", philo->dt->start,
        philo->id, (unsigned long)pthread_self(), philo->dt, (void *)philo->f_fork, (void *)philo->s_fork);
    pthread_mutex_unlock(philo->dt->mut_stdout);
    pthread_mutex_unlock(philo->f_fork);
    pthread_mutex_unlock(philo->s_fork);
    ///////////////////////////////////////////////////////
    
    ///////////////////////
    pthread_mutex_lock(philo->dt->mut_stdout);
    printf("Thread [%d] id : %lu dort.\n",
        philo->id, (unsigned long)pthread_self());
    pthread_mutex_unlock(philo->dt->mut_stdout);
    usleep(600);
    ///////////////////////
    // }
    
    return NULL;
}


int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    t_data   *dt;
    t_philo* head;
    t_philo* new_node;
    t_philo* current;
    int      i;

    pthread_mutex_t alf_fork[NB_PHILO];

    head = NULL;
    new_node = NULL;
    current = NULL;
    dt = malloc(sizeof(t_data));
    dt->mut_start = NULL;
    dt->mut_start = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(dt->mut_start, NULL);
    dt->mut_stdout = NULL;
    dt->mut_stdout = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(dt->mut_stdout, NULL);
    dt->start = 0;
    i = 0;
    while (i < NB_PHILO)
    {
        pthread_mutex_init(&alf_fork[i], NULL);
        i++;
    }
    i = 0;
    while (i < NB_PHILO)
    {
        new_node = malloc(sizeof(t_philo));
        new_node->id = i;
        if (new_node->id % 2 == 0)
        {
            new_node->f_fork = &alf_fork[i];
            new_node->s_fork = &alf_fork[(i + 1) % NB_PHILO];
        }   
        else
        {
            new_node->s_fork = &alf_fork[i];
            new_node->f_fork = &alf_fork[(i + 1) % NB_PHILO];
        }
        new_node->dt = dt;
        new_node->next = NULL;
        if (!head)
            head = new_node;
        else
            current->next = new_node;
        current = new_node;
        i++;
    }

    current = head;
    i = 0;
    while (i < NB_PHILO)
    {
        pthread_create(&current->thread, NULL, thread_function, (void*)current);
        //Quand tous les threads sont pret on mesure l'heure (il faut tous les attendre)
        current = current->next;
        i++;
    }
    pthread_create(&monitor, NULL, thread_monitor, dt);//NULL car pas de mutex a atteindre pour l'instant
    // On met la dummy start a 1 ce qui permet a thread_function de partir dans le while
    pthread_join(monitor, NULL);
    current = head;
    i = 0;
    while (i < NB_PHILO)
    {
        pthread_join(current->thread, NULL);
        current = current->next;
        i++;
    }
    i = 0;
    while (i < NB_PHILO)
    {
        pthread_mutex_destroy(&alf_fork[i]);
        i++;
    }

    dt->philos = head;
    current = head;
    i = 0;
    while (i < NB_PHILO)
    {
        t_philo *temp = current;
        current = current->next;
        free(temp);
        i++;
    }
    pthread_mutex_destroy(dt->mut_stdout);
    pthread_mutex_destroy(dt->mut_start);
    free(dt->mut_start);
    free(dt->mut_stdout);
    free(dt);
    printf("Tous les threads ont terminé. La valeur de mail est : %d\n", mail);
    
    
    return (0);
}