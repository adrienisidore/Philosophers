/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:41:00 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/06 15:54:13 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define PARAM_ERROR     "philo:./philo n t_die t_eat t_sleep [many_meal]\n"
# define INV_ARG         "philo: Invalid argument(s)"
# define TMANY_PHILO     "philo: too many philosophers\n"
# define MEM_FAIL        "philo: Memory allocation failed\n"
# define MUT_FAIL        "philo: Mutex initialisation failed\n"
# define TH_FAIL         "philo: Thread creation failed\n"
# define THC_FAIL        "philo: Thread connexion failed\n"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mut;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_mut			*f_fork;
	t_mut			*s_fork;
	long			last_meal;
	long			nb_meal;
	t_data			*dt;
	struct s_philo	*next;
}	t_philo;

typedef struct s_data
{
	int			start;
	int			fail;
	long		start_time;
	long		nphilo;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	long		many_eat;
	t_mut		mut_start;
	t_mut		mut_stdout;
	t_mut		*forks;
	t_mut		mut_lastmeal;
	t_mut		mut_nbmeal;
	t_mut		mut_startime;
	t_mut		mut_fail;
	pthread_t	monit;
	t_philo		*philos;
}	t_data;

//main.c
int			ft_exit(char *to_write);
void		ft_destroy(t_mut *mut1, t_mut *mut2, t_mut *mut3, t_mut *mut4);
int			ft_freeall(t_mut *forks, t_philo *lst_philo, t_data *dt, char *str);

//ft_parser.c
char		**ft_parser(int ac, char **av);

//utils.c
size_t		ft_strlen(const char *str);
long int	ft_atol(const char *str);
char		*ft_ltoa(long n);

//ft_setget.c
void		ft_setint(t_mut *mut_, int *to_set, int value);
void		ft_setlong(t_mut *mut_, long *to_set, long value);
int			ft_getint(t_mut *mut_, int *to_get);
long		ft_getlong(t_mut *mut_, long *to_get);

//ft_inidt.c
t_data		*ft_inidt(int ac, char **av);

//sim_utils.c
void		ft_write(t_philo *philo, int id, char *str);
void		ft_think(t_data *dt);
void		ft_sleep(long usec, t_data *dt);
long		ft_time(struct timeval time);

//sim.c
long		ft_time(struct timeval time);
void		*ft_monitor(void *arg);
void		*ft_philos(void *arg);

#endif