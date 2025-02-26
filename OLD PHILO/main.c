/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:40:49 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/25 13:06:54 by aisidore         ###   ########.fr       */
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
//Tous les philos ont acces a leur 2 fourchettes des le debut (autant de fourchettes que de philo)
//a celui qui ira le + pour lock les 2 fourchettes
void    *ft_thread(void *arg)
{
    t_data          *dt;
    int             i;

    //On recupere le mutex et on protege la data
    dt = (t_data *)arg;

    //i est une variable locale, chaque CPU en  une copie
    i = 0;
    write(1, "Test from threads\n", 19);
    
    //1 permettre a chaque philo d'acceder a dt->mut
    //2 changer l'argument de ft_thread pour qu'il recupere chaque mutex plutot que dt en argument
    //afficher l'idx du thread qui incremente
    while (i < 10)
    {
        pthread_mutex_lock(dt->mut);//Pour l'instant y'a qu'un seul mutex dans dt, et tous les threads l'utilisent pour incrementer mails
        //On peut faire UNE PREMIERE SIMULATION OU ON FAIT ECRIRE CHAQUE PHILO SON IDENTIFIANT ET C TOUT (UN MUTEX WRITE).
        //ILS VONT SUREMENT ECRIRE UN PEU DANS LE DESORDRE ?

        //Si je veux bloquer la donnee avec 2 mutex (fourchettes droite et gauche) il me suffit
        //d'ecrire les 2 mutex a la suite ?
        //pthread_mutex_lock(dt->philos->r_fork);
        //pthread_mutex_lock(dt->philos->l_fork);
        //write(1, "I'm eating ...", 15);
        //pthread_mutex_unlock(dt->philos->r_fork);
        //pthread_mutex_unlock(dt->philos->l_fork);
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
    dt->t_eat = ft_atol(av[3]);
    dt->t_sleep = ft_atol(av[4]);
    // dt->t_think non initialise
    if (ac == 6)
        dt->many_eat = ft_atol(av[5]);
    else
        dt->many_eat = -1;
}

void    ft_initphilos(t_data *dt)
{
    long    i;

    i = 0;
    while (i < dt->nphilo) // Correction : `i` commence à 0 et va jusqu'à `nphilo - 1`
    {
        //avant j'ecrivais dt->philos->idx = i + 1; ce qui correspondait uniquement a l'indice du 1er philo
        //qui etait constamment ecrase
        dt->philos[i].idx = i + 1; // Assigner un identifiant unique (de 1 à nphilo)
        dt->philos[i].dt = dt; // Associer chaque philosophe à la structure `dt`
        i++;
    }
}


void    ft_freeall(t_data *dt, pthread_mutex_t *dt_mut, t_philo *dt_philos, char *str)
{
    if (dt_mut)
    {
        //Si je fais appel a la fonction pour tout nettoyer c'est forcement qu'on est a un
        //endroit critique ou il faut detruire le mutex (soit dans ft_init, soit ft_inithreads,
        //soit a la fin du main). On creera plus tard ft_destroy pour detruire tous les mutex
        if (dt && dt_mut && dt_philos)
            pthread_mutex_destroy(dt->mut); 
        free(dt_mut);//Quand y'en aura pleins on fera une boucle   
    }
    if (dt_philos)
        free(dt_philos);
    if (dt)
        free(dt);
    //si str : lancer ft_exit sans message (str = NULL alors exit 0)
    if (str)
        ft_exit(str);
    ft_exit(NULL);
}

t_data  *ft_init(int ac, char **av)
{
    t_data      *dt;

    dt = malloc(sizeof(t_data));
    if (!dt)
        ft_exit(MEM_FAIL);
    ft_initdt(dt, ac, av);//tout ce qui n'est pas du malloc s'init ici
    dt->mut = malloc(sizeof(pthread_mutex_t));//Ici on initialise qu'un seul mutex
    if (!dt->mut)
        ft_freeall(dt, NULL, NULL, MEM_FAIL);




    //Je malloc les mutex mut_fork (fourchette droite pour commencer)
    //dt->mut_fork = malloc(sizeof(pthread_mutex_t) * dt->nphilo);
    //if (!dt->mut_fork)
    //    ft_freeall(dt, NULL, NULL, MEM_FAIL);//Pour etre exacte il faudrait aussi free dt->mut
    //mais il s'agit juste d'une etape intermediaire
    ///////////////////////////////////////////////////////////////////






    dt->philos = malloc(sizeof(t_philo) * dt->nphilo);
    if (!dt->philos)
        ft_freeall(dt, dt->mut, NULL, MEM_FAIL);
    //MALLOC autant de mutex qu'il y a de fourchettes (philos). MALLOC autant de thread qu'il y a de philos + 1 monitor
    if (pthread_mutex_init(dt->mut, NULL))
        ft_freeall(dt, dt->mut, dt->philos, MUT_FAIL);//Dans le cas ou je cree 1 seul mutex.






    //On initialise ensuite toutes les fourchettes :
    //int i;
    //i = 0;
    //while (i < dt->nphilo)
    //{
    //    if (pthread_mutex_init(&dt->mut_fork[i], NULL))
    //        ft_freeall(dt, dt->mut_fork, NULL, MUT_FAIL);
    //    i++;
    //}
    ////////////////////////////////////////////////


    //Dans ft_initphilos on devra ensuite ajouter
    //i = 0;
    //while (i < dt->nphilo)
    //{
    //    // Cette logique peut elle etre mis dans une fonction avec une copie de dt ?
    //    //Je me pose la question a cause du &dt->mut_fork.
    //    dt->philos[i].r_fork = &dt->mut_fork[i];
    //    dt->philos[i].l_fork = NULL;
    //    i++;
    //}
    




    ft_initphilos(dt);//pas de malloc ici donc pas besoin de free. On a initialise les philos plus haut donc pas de risque de
    //mauvias indexage. Ils sont ous deja pret a etre remplis ici.
    return (dt);
}
// void    ft_wait()
// {

// }

//Demander a GPT si il voit des ameliorations niveau protection car j'ai un peu fait a la onegain,
//Surtout pour join. Si un join foire mais que les suivants pourrait fonctionner (ex le 3eme sur 5 foire)
//est ce que c'est bien protege ?
void    ft_inithreads(t_data *dt)
{
    pthread_t       *th;
    int             i;
    
    //Il faut creer un thread de + : le moniteur. Le moniteur ne va a priori pas
    //utiliser ft_thread
    th = malloc(sizeof(pthread_t) * dt->nphilo);
    i = 0;
    while (i < dt->nphilo)
    {
        if (pthread_create(&th[i], NULL, &ft_thread, dt))
        {
            while (--i >= 0)
                pthread_join(dt->philos[i].thread, NULL);
            ft_freeall(dt, dt->mut, dt->philos, TH_FAIL);
        }
        i++;
    }
    i = 0;
    while (i < dt->nphilo)
    {
        if (pthread_join(th[i], NULL))
            ft_freeall(dt, dt->mut, dt->philos, THC_FAIL);
        i++;
    }
    free(th);//Ici pour le moment, mais peut etre useless plus tard   
}

//Faire une fonction qui fait peter les malloc, les pthread create et les pthread_join
int main(int ac, char **av)
{
    t_data          *dt;

    dt = ft_init(ac, ft_parser(ac, av));
    
    ft_inithreads(dt);

    // //On detruit le mutex une seule fois, meme si les threads ont echoue a join ou autre.
    // //Comme ca aucun risque de le detruire plusieurs fois.
    // pthread_mutex_destroy(dt->mut);//ft_destroy pour detruire tous les mutex

    //Le resultat joint de plusieurs threads se situera apres les pthread_join
    printf("mail = %d\n", mail);

    ft_freeall(dt, dt->mut, dt->philos, NULL);
    return (0);
}