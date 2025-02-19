/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:40:49 by aisidore          #+#    #+#             */
/*   Updated: 2025/02/19 15:35:34 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
int	mails = 0;
// pthread_mutex_t mut;//locker

void    ft_error(char *to_write)
{
	if (to_write)
		write(2, to_write, ft_strlen(to_write));
	exit(1);
}

void    *ft_thread(void *arg)
{
	int	i;
	pthread_mutex_t *mut;

	mut = (pthread_mutex_t *)arg;
	i = 0;
	write(1, "Test from threads\n", 19);
	while (i < 100)
	{//1000000 : sinon on remarque pas le datarace
		pthread_mutex_lock(mut);
		mails++;
		i++;
		pthread_mutex_unlock(mut);
	}
	return (NULL);
}

static t_data    *ft_initdt(int ac, char **av)
{
	//Ici on initialise la structure data ainsi que les philos a l'interieur
	//Si un des malloc fail alors on free tous ceux deja fait ainsi que la structure data en elle meme
	t_data			*dt;

	(void)av;
	dt = malloc(sizeof(t_data));//comprend pas le message d'erreur
	if (!dt)
		ft_error("philo: Memory allocation failed\n");
	dt->t_die = (int)ft_atol(av[2]);
	dt->t_eat = (int)ft_atol(av[3]);
	dt->t_sleep = (int)ft_atol(av[4]);
	dt->t_think = 0;//pour le moment, arbitraire
	if (ac == 6)
		dt->many_eat = (int)ft_atol(av[5]);	
	dt->philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
	if (dt->philos)
	{
		free(dt);
		ft_error("philo: Memory allocation failed\n");
	}
	return (dt);
}

int main(int ac, char **av)
{
	pthread_t       t1;
	pthread_t		t2;
	pthread_mutex_t mut;//locker
	t_data          *dt;

	ft_parser(ac, av);
	dt = ft_initdt(ac, av);
	free(dt->philos);
	free(dt);
	// 1 mutex pour proteger 1 donnee. 1er arrive 1er servi
	//NULL : des param useless pour nous
	pthread_mutex_init(&mut, NULL);
	
	//Connexion entre l'API thread et la fonction qu'elle va executer :
	//1er NULL : set up les parametres par defaut. En dernier argument c'est les arguments que
	//ft_thread recquiert pour fonctionner.
	//J'aurais pu aussi initialiser mut dans ft_thread ? et ecrire
	//pthread_create(&t1, NULL, &ft_thread, NULL) ??
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
	printf("mails = %d\n", mails);
	
	return (0);
}