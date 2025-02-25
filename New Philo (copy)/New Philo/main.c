/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:53:12 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/25 18:31:15 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mail = 0;

// t_philo* ft_create_threads(pthread_mutex_t* mutex)
// {
//     t_philo* new_node;
    
//     new_node = (t_philo*)malloc(sizeof(t_philo));
//     new_node->mutex = mutex;
//     new_node->next = NULL;
//     return (new_node);
// }

// void *thread_function(void *arg)
// {
//     t_philo *philo = (t_philo *)arg;

//     // printf("id philo = %d\n", philo->id);
//     // Les threads pairs commencent, les impairs attendent
//     if (philo->id % 2 != 0)
//         usleep(300); // Les impairs attendent un peu pour laisser les pairs commencer

    
//     pthread_mutex_lock(philo->l_fork);
//     pthread_mutex_lock(philo->r_fork); // Vérifie si le deuxième mutex est dispo
//     // printf("id = %d\nl-fork = %p, r-fork = %p\n", philo->id, philo->l_fork,  philo->r_fork);
//     pthread_mutex_unlock(philo->r_fork);

//     pthread_mutex_unlock(philo->l_fork);
    
//     // printf("Thread %d a accès aux deux mutex et affiche son message !\n", philo->id);
//     usleep(1000000); // Petite pause pour éviter la saturation CPU
//     return NULL;
// }

void *thread_function(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // Les threads impairs attendent un peu pour éviter la compétition immédiate
    if (philo->id % 2 != 0)
        usleep(1000);

    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(philo->l_fork);   
    }
    else
    {
        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(philo->r_fork);
    }

    printf("Thread %d a accès aux deux mutex et affiche son message !\n", philo->id);

    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);

    // usleep(1000000); // Petite pause pour éviter la saturation CPU
    return NULL;
}


int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    t_philo* head;
    t_philo* new_node;
    t_philo* current;
    int      i;

    pthread_mutex_t all_fork[5];

    head = NULL;
    new_node = NULL;
    current = NULL;
    i = 0;
    while (i < 5)
    {
        pthread_mutex_init(&all_fork[i], NULL);
        i++;
    }
    i = 0;
    while (i < 5)
    {
        new_node = malloc(sizeof(t_philo));
        new_node->id = i;
        new_node->l_fork = &all_fork[i];
        new_node->r_fork = &all_fork[(i + 1) % 5];
        new_node->next = head;
        if (!head)
            head = new_node;
        else
            current->next = new_node;
        current = new_node;
        i++;
    }
    current->next = head; // Boucle circulaire

    current = head;
    i = 0;
    while (i < 5)
    {
        pthread_create(&current->thread, NULL, thread_function, (void*)current);
        current = current->next;
        i++;
    }
        
    // Attendre la fin de tous les threads
    current = head;
    i = 0;
    while (i < 5)
    {
        pthread_join(current->thread, NULL);
        current = current->next;
        i++;
    }
    i = 0;
    while (i < 5)
    {
        pthread_mutex_destroy(&all_fork[i]);
        i++;
    }

    current = head;
    i = 0;
    while (i < 5)
    {
        t_philo *temp = current;
        current = current->next;
        free(temp);
        i++;
    }

    printf("Tous les threads ont terminé. La valeur de mail est : %d\n", mail);
    
    
    return (0);
}