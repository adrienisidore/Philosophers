/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:40:49 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/18 13:58:19 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Si time_to_die > time_to_eat alors après time_to_die milisecondes tous les philo
//(paires/impairs) qui ont pas eu de fourchettes meurent.

void    ft_error(char *to_write)
{
    write(2, to_write, ft_strlen(to_write));
    exit(1);
}


// static void    ft_initdt(t_data *dt, char **av)
// {
//     //Ici on initialise la structure data ainsi que les philos a l'interieur
//     //i un des malloc fail alors on free tous ceux deja fait ainsi que la structure data en elle meme
    
//     // dt->philos = malloc(sizeof(t_philo));//comprend pas le message d'erreur
//     // if (!dt->philos)
//     // {
//     //     free(dt);
//     //     ft_error("philo: Memory allocation failed\n");   
//     // }
    
// }

int main(int ac, char **av)
{
    pthread_mutex_t mut;//locker
    t_data          *dt;

    ft_parser(ac, av);
    dt = malloc(sizeof(t_data));
    if (!dt)
        ft_error("philo: Memory allocation failed\n");
    //Il faudra free aussi tous les philos a l'interieur
    free(dt);


    
    //Je crois qu'il faut creer/detruire autant de mutex qu'il y a de philos
    pthread_mutex_init(&mut, NULL);
    
    // pthread_mutex_lock(&mut);//ferme le locker
    // tout ce qu'il y a entre les 2 ne sera execute
    // que par 1 thread.
    // pthread_mutex_unlock(&mut);//ouvre le locker
    printf("Hello World\n");
    printf("int max %d int min %d\n", INT_MAX, INT_MIN);

    //Je crois qu'il faut creer/detruire autant de mutex qu'il y a de philos
    pthread_mutex_destroy(&mut);




    
    return (0);
}