/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:59:46 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/04 19:51:48 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Pourrait etre static non ? Si oui retirer proto .h
long    ft_time(struct timeval time)
{
	long	res;

	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}

//static ? Si non ajouter proto dans .h
void	ft_sleep(long usec)
{
	struct timeval	time;
	long			curr_time;
	long			begin;

	gettimeofday(&time, NULL);
	begin = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (1)
	{
		gettimeofday(&time, NULL);
		curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
		if (curr_time - begin < usec)
			usleep(500);//WHY ?? Demander a Paul
		else
			break ;
	}
}

static void	ft_putstr_fd(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		write(1, &str[i], 1);
}

void	ft_write(t_philo *philo, int id, char *str)
{
	struct timeval	time;//On en a besoin pour recuperer la valeur de last_meal

    (void)id;
    (void)str;
	pthread_mutex_lock(&philo->dt->mut_stdout);
    if (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
    {
        // pthread_mutex_unlock(philo->f_fork);
        // pthread_mutex_unlock(philo->s_fork);
        pthread_mutex_unlock(&philo->dt->mut_stdout);
        return ;   
    }
    gettimeofday(&time, NULL);
    ft_putstr_fd(ft_ltoa(ft_time(time) - ft_getlong(&philo->dt->mut_startime,
		&philo->dt->start_time)));
    ft_putstr_fd(" ");
    ft_putstr_fd(ft_ltoa((long) id));
    ft_putstr_fd(" ");
    ft_putstr_fd(str);
    //Erika utilise un flag pour arreter d'ecrire
    pthread_mutex_unlock(&philo->dt->mut_stdout);

}

//handle_i permet d'incrementer i. Si on est a la fin et que tous les philos sont full
//alors on arrete la simulation ou alors on remet i a 0 et all_full a 0. Sinon i++
//ft_next

static void     ft_next(t_philo **ptr_curr, t_data *dt, int *being_full)
{
    //Si on a atteint le dernier noeud
    if ((*ptr_curr)->next == NULL)
    {
        //On check si tous les philos sont pleins (il y a nphilo qui sont full).
        //Si c'est pas le cas on recommence
        if (*being_full == dt->nphilo)
            ft_setint(&dt->mut_start, &dt->start, 0);
        else
        {
            *ptr_curr = dt->philos;
            *being_full = 0;
        }
    }
    else
        *ptr_curr = (*ptr_curr)->next;
    ft_sleep(100);//WHY ??
}

void *ft_monitor(void *arg)
{
    t_data          *dt;
    struct timeval  time;
    t_philo         *curr;
    int             being_full;

    dt = (t_data *)arg;
    being_full = 0;
    //Le monitor met a jour les last_meal de tous les philos
    gettimeofday(&time, NULL);
    dt->start_time = ft_time(time);
    curr = dt->philos;
    while (curr)
    {
        if (dt->many_eat >= 0)
            curr->is_full = 0;//Chaque philo va indiquer quand il est full
        curr->last_meal = ft_time(time);
        curr = curr->next;
    }
    //Le monitor lance la simulation
    ft_setint(&dt->mut_start, &dt->start, 1);

    ft_sleep(50);//Atteindre un peu avant de checker
    
    curr = dt->philos;
    while (ft_getint(&dt->mut_start, &dt->start))
    {
        gettimeofday(&time, NULL);
        if (ft_time(time) - ft_getlong(&dt->mut_lastmeal,
            &curr->last_meal) > dt->t_die)
        {
            ft_write(curr, curr->id, "has died\n");
            ft_setint(&dt->mut_start, &dt->start, 0);
        }
        if (dt->many_eat != -1 && ft_getlong(&dt->mut_nbmeal,
            &curr->nb_meal) > dt->many_eat)
            being_full++;
        ft_next(&curr, dt, &being_full);//A CODER
    }


    
    
    ////////////////////////////////
    //Le monitor compare l'heure actuelle avec l'heure a laquelle il a mange pour la derniere fois (last_meal est dans dt)
    //et si le monitor constate que la deadline est depassee alors il met une dummy a 1 dans dt, et tous les threads ayant
    //acces a cette dummy s'arretent.
    // ft_sleep(1000);
    // ft_setint(&dt->mut_start, &dt->start, 0);
    //Checker le temps que prend chaque philo en permanence
    return (NULL);
}
//SAVOIR EXPLIQUER
static void	ft_think(t_data *dt)
{
	long	time;

	if (dt->nphilo % 2 == 0)
		return ;
	time = dt->t_eat * 2 - dt->t_sleep;
	if (time < 0)
		time = 0;
	ft_sleep(time);
}

// printf("(start %d)Thread [%d] a pris 1 fourchette. (f_fork: %p, s_fork: %p)\n", ft_getint(&philo->dt->mut_start, &philo->dt->start),
        // philo->id, (void *)philo->f_fork, (void *)philo->s_fork);
void *ft_philos(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    struct timeval	time;

    if (philo->dt->nphilo == 1)//Le monitor se charge de dire qui est mort
        return (ft_write(philo, philo->id, "has taken a fork\n"), NULL);
    while (!ft_getint(&philo->dt->mut_start, &philo->dt->start))
        ft_sleep(1);
    if (philo->id % 2 != 0)
        ft_sleep(30);

    while (ft_getint(&philo->dt->mut_start, &philo->dt->start))
    {
        pthread_mutex_lock(philo->s_fork);
        ft_write(philo, philo->id, "has taken a fork\n");
        pthread_mutex_lock(philo->f_fork);
        ft_write(philo, philo->id, "has taken a fork\n");
        gettimeofday(&time, NULL);
        ft_setlong(&philo->dt->mut_lastmeal, &philo->last_meal, ft_time(time));
        ft_write(philo, philo->id, "is eating\n");
        pthread_mutex_lock(&philo->dt->mut_nbmeal);
        philo->nb_meal = philo->nb_meal + 1;
        pthread_mutex_unlock(&philo->dt->mut_nbmeal);
        pthread_mutex_unlock(philo->f_fork);
        pthread_mutex_unlock(philo->s_fork);

        ft_write(philo, philo->id, "is sleeping\n");
        ft_sleep(philo->dt->t_sleep);//Pas besoin de le proteger ?

        ft_write(philo, philo->id, "is thinking\n");
        ft_think(philo->dt);
    }
    return (NULL);
}