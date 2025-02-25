/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:53:12 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/25 17:31:27 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mail = 0;

t_philo* ft_create_threads(pthread_mutex_t* mutex)
{
    t_philo* new_node;
    
    new_node = (t_philo*)malloc(sizeof(t_philo));
    new_node->mutex = mutex;
    new_node->next = NULL;
    return (new_node);
}

void* thread_function(void* arg)
{
    t_philo* philo;
    
    philo = (t_philo*)arg;
    printf("Thread %lu en cours d'exécution.\n", (unsigned long)pthread_self());
    usleep(2000);//On attend tout le monde
    pthread_mutex_lock(philo->mutex); // Acquisition du mutex
    printf("Thread %lu incremente mail...\n", (unsigned long)pthread_self());
    mail++; // Incrémentation
    pthread_mutex_unlock(philo->mutex); // Libération du mutex
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
    pthread_mutex_t mutex;

    head = NULL;
    new_node = NULL;
    current = NULL;
    pthread_mutex_init(&mutex, NULL);
    i = 0;
    while (i < 5)
    {
        new_node = ft_create_threads(&mutex);
        // pthread_create(&new_node->thread, NULL, thread_function, NULL);
        pthread_create(&new_node->thread, NULL, thread_function, (void*)new_node);
        if (!head)
            head = new_node;
        else
            current->next = new_node;
        current = new_node;
        i++;
    }
    // Attendre la fin de tous les threads
    current = head;
    while (current)
    {
        pthread_join(current->thread, NULL);
        current = current->next;
    }
    //Tout liberer
    current = head;
    t_philo* tmp;
    while (current)
    {
        tmp = current;
        current = current->next;
        free(tmp);
    }

    printf("Tous les threads ont terminé. La valeur de mail est : %d\n", mail);

    // Détruire le mutex
    pthread_mutex_destroy(&mutex);
    
    
    return (0);
}