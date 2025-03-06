/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:53:12 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/06 20:10:37 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Supp executable + les .o////////////////////////////////////////////////////////////

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*dt;
	t_philo	*curr;

	if (!ft_parser(ac, av))
		return (0);
	dt = ft_inidt(ac, ft_parser(ac, av));
	if (!dt || dt->forks == NULL || dt->philos == NULL)
		return (1);
	curr = dt->philos;
	while (curr)
	{
		if (pthread_create(&curr->thread, NULL, ft_philos, (void *)curr))
			return (ft_fail(dt, curr));
		curr = curr->next;
	}
	if (pthread_create(&dt->monit, NULL, ft_monitor, dt))
		return (ft_fail(dt, curr));
	pthread_join(dt->monit, NULL);
	curr = dt->philos;
	while (curr)
	{
		pthread_join(curr->thread, NULL);
		curr = curr->next;
	}
	pthread_mutex_destroy(&dt->mut_fail);
	return (ft_freeall(dt->forks, dt->philos, dt, NULL));
}
