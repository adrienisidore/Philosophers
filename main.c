/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:40:49 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/11 12:43:39 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Si time_to_die > time_to_eat alors après time_to_die milisecondes tous les philo
//(paires/impairs) qui ont pas eu de fourchettes meurent.

static int ft_init(int ac, char **av, pthread_mutex_t *mut)
{
    pthread_mutex_init(mut, NULL);
    ft_parser(ac, av);

    return (0);
}

int main(int ac, char **av)
{
    pthread_mutex_t mut;//locker
    
    // pthread_mutex_init(&mut, NULL);
    // ft_parser(ac, av);

    ft_init(ac, av, &mut);
    
    // pthread_mutex_lock(&mut);//ferme le locker
    // tout ce qu'il y a entre les 2 ne sera execute
    // que par 1 thread.
    // pthread_mutex_unlock(&mut);//ouvre le locker
    printf("Hello World\n");

    pthread_mutex_destroy(&mut);

    return (0);
}