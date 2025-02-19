/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:40:49 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/19 19:03:59 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//penser au cas ou y'a 1 seul philo

//gcc -S main.c utils.c parsing.c : obtenir le comportement CPU (Code Vault : What are race conditions ? 10min)
//Peu d'iteration ne pose pas de pb car le 2eme thread n'a pas le temps d'etre cree avant
//que le premier finisse son iteration


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
    t_data          *dt;
    int             i;

    //On recupere le mutex et on protege la data
    dt = (t_data *)arg;

    i = 0;
    write(1, "Test from threads\n", 19);
    while (i < 1000000)
    {
        pthread_mutex_lock(dt->mut);
        mail++;
        pthread_mutex_unlock(dt->mut);
        i++;
    }
    return (NULL);
}
void    ft_initdt(t_data *dt, int ac, char **av)
{
    // pthread_t   *th;
    
    
    dt->nphilo = ft_atol(av[1]);
    dt->t_die = ft_atol(av[2]);
    dt->t_die = ft_atol(av[3]);
    dt->t_sleep = ft_atol(av[4]);
    // dt->t_think non initialise
    if (ac == 6)
        dt->many_eat = ft_atol(av[5]);
    else
        dt->many_eat = -1;
    dt->philos = malloc(sizeof(t_data) * dt->nphilo);
    if (!dt->philos)
    {
        pthread_mutex_destroy(dt->mut);
        free(dt->mut);
        free(dt);
        ft_error("philo: Memory allocation failed\n");
    }
    // th = malloc(sizeof(pthread_t))
}

void    ft_initphilos(t_data *dt)
{
    long    i;

    i = 1;
    while (i <= dt->nphilo)
    {
        dt->philos->idx = i;
        dt->philos->dt = dt;
        i++;
    }
    //Si un seul create_thread foire il faut free dt etc...
    
}

t_data  *ft_init(int ac, char **av)
{
    t_data      *dt;

    dt = malloc(sizeof(t_data));
    if (!dt)
        ft_error("philo: Memory allocation failed\n");
    dt->mut = malloc(sizeof(pthread_mutex_t));
    if (!dt->mut)
    {
        free(dt);
        ft_error("philo: Memory allocation failed\n");
    }
    pthread_mutex_init(dt->mut, NULL);//Dans le cas ou je cree 1 seul mutex, situe dans dt
    //A FAIRE A FAIRE
    ft_initdt(dt, ac, av);//tout ce qui n'est pas du malloc
    ft_initphilos(dt);//idem pour les
    return (dt);
}
// void    ft_wait()
// {

// }

int main(int ac, char **av)
{
    pthread_t       t1;
    pthread_t       t2;
    t_data          *dt;

    dt = ft_init(ac, ft_parser(ac, av));
    //Il faudra free aussi tous les philos a l'interieur
    
    //Connexion entre l'API thread et la fonction qu'elle va executer :
    //1er NULL : set up les parametres par defaut. En dernier argument c'est les arguments que
    //ft_thread recquiert pour fonctionner. De base on avait mis NULL mais ca oblige a declarer mut en variable globale
    if (pthread_create(&t1, NULL, &ft_thread, dt))
        ft_error("philo: Thread creation failed\n");//il faut free aussi le tableau
    if (pthread_create(&t2, NULL, &ft_thread, dt))
        ft_error("philo: Thread creation failed\n");

    //L'equivalent de wait() pour les threads :
    //le 2eme argument permet de recuperer le resultat final du thread mais ici on renvoie un void
    if (pthread_join(t1, NULL))
        ft_error("philo: Thread connexion failed\n");
    if (pthread_join(t2, NULL))
        ft_error("philo: Thread connexion failed\n");

    pthread_mutex_destroy(dt->mut);

    //Le resultat joint de plusieurs threads se situera apres les pthread_join
    printf("mail = %d\n", mail);

    free(dt->mut);
    free(dt->philos);
    free(dt);
    return (0);
}