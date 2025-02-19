/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:40:49 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/19 17:53:46 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//penser au cas ou y'a 1 seul philo

// -no-pie

//gcc -S main.c utils.c parsing.c : obtenir le comportement CPU (Code Vault : What are race conditions ? 10min)
//Peu d'iteration ne pose pas de pb car le 2eme thread n'a pas le temps d'etre cree avant
//que le premier finisse son iteration

//-no-pie ajoute pour eviter message d'erreur

//Quand je cree un thread c'est pour executer une fonction.
//Pour creer un thread il faut creer une variable qui va contenir l'info que l'API thread renvoie :
//une variable de type pthread_t. Pour initialiser la connexion entre la fonction routine et le thread,
// on utilise pthread_create()

//gcc ou cc pour la compil ?

//Si time_to_die > time_to_eat alors après time_to_die milisecondes tous les philo
//(paires/impairs) qui ont pas eu de fourchettes meurent.

int mail = 0;

void    ft_error(char *to_write)
{
    if (to_write)
        write(2, to_write, ft_strlen(to_write));
    exit(1);
}

void    *ft_thread(void *arg)
{
    pthread_mutex_t *ptr_mut;
    int             i;

    //On recupere le mutex et on protege la data
    ptr_mut = (pthread_mutex_t *)arg;

    i = 0;
    pthread_mutex_lock(ptr_mut);
    write(1, "Test from threads\n", 19);
    while (i < 1000000)
    {
        mail++;
        i++;
    }
    pthread_mutex_unlock(ptr_mut);
    return (NULL);
}
void    ft_initdt(t_data *dt, int ac, char **av)
{
    dt->t_die = ft_atol(av[2]);
    dt->t_die = ft_atol(av[3]);
    dt->t_sleep = ft_atol(av[4]);
    // dt->t_think non initialise
    if (ac == 6)
        dt->many_eat = ft_atol(av[5]);
    else
        dt->many_eat = -1;
    dt->philos = malloc(sizeof(t_data) * ft_atol(av[1]));
}

t_data  *ft_init(int ac, char **av)
{
    t_data      *dt;

    (void)ac;
    (void)av;
    dt = malloc(sizeof(t_data));
    if (!dt)
        ft_error("philo: Memory allocation failed\n");
    // ft_initdt(dt, ac, av);
    return (dt);
}

int main(int ac, char **av)
{
    pthread_t       t1;
    pthread_t       t2;
    pthread_mutex_t mut;//locker
    t_data          *dt;

    // ft_parser(ac, av);
    dt = ft_init(ac, ft_parser(ac, av));
    //Il faudra free aussi tous les philos a l'interieur
    

    // //Je crois qu'il faut creer/detruire autant de mutex qu'il y a de philos
    //NULL : des param useless pour nous
    pthread_mutex_init(&mut, NULL);
    
    //Connexion entre l'API thread et la fonction qu'elle va executer :
    //1er NULL : set up les parametres par defaut. En dernier argument c'est les arguments que
    //ft_thread recquiert pour fonctionner. De base on avait mis NULL mais ca oblige a declarer mut en variable globale
    if (pthread_create(&t1, NULL, &ft_thread, &mut))
        ft_error("philo: Thread creation failed\n");
    if (pthread_create(&t2, NULL, &ft_thread, &mut))
        ft_error("philo: Thread creation failed\n");

    //L'equivalent de wait() pour les threads :
    //le 2eme argument permet de recuperer le resultat final du thread mais ici on renvoie un void
    if (pthread_join(t1, NULL))
        ft_error("philo: Thread connexion failed\n");
    if (pthread_join(t2, NULL))
        ft_error("philo: Thread connexion failed\n");

    // //Je crois qu'il faut creer/detruire autant de mutex qu'il y a de philos
    pthread_mutex_destroy(&mut);

    //Le resultat joint de plusieurs threads se situera apres les pthread_join
    printf("mail = %d\n", mail);


    free(dt);
    return (0);
}