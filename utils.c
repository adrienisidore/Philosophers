/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:41:04 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/06 18:18:53 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_dispatch(t_philo *new_philo, t_data *dt, int j)
{
	new_philo->dt = dt;
	new_philo->nb_meal = 0;
	new_philo->id = j;
	if (new_philo->id % 2 == 0)
	{
		new_philo->f_fork = &dt->forks[j - 1];
		new_philo->s_fork = &dt->forks[j % dt->nphilo];
	}
	else
	{
		new_philo->s_fork = &dt->forks[j - 1];
		new_philo->f_fork = &dt->forks[j % dt->nphilo];
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

long int	ft_atol(const char *str)
{
	int			i;
	int			sign;
	long int	r;

	i = 0;
	sign = 1;
	r = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i++] - '0';
		if (r > INT_MAX)
			return (-1);
	}
	return (r * sign);
}

static int	ft_size(long nb)
{
	int	res;

	res = 0;
	if (!nb)
		return (1);
	if (nb < 0)
	{
		res++;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		res++;
	}
	return (res);
}

char	*ft_ltoa(long n)
{
	static char	str[100];
	int			len;
	long		nb;

	nb = (long)n;
	len = ft_size(nb);
	if (nb < 0)
		nb = nb * -1;
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = (nb % 10) + '0';
		nb = nb / 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
