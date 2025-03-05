/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:40:44 by aisidore          #+#    #+#             */
/*   Updated: 2025/03/05 18:13:20 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isnum(const char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_ispace(const char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static int	ft_checkint(const char *str, int n_arg)
{
	int	i;
	int	j;

	i = 0;
	while (ft_ispace(str[i]))
		i++;
	if (!(ft_isnum(str[i]) || str[i] == '+'))
		return(ft_exit(INV_ARG));
	if (str[i] == '+')
		i++;
	j = 0;
	while (ft_isnum(str[i]))
	{
		i++;
		j++;
	}
	if (j > 10)
		return (ft_exit(INV_ARG));
	while (ft_ispace(str[i]))
		i++;
	if (str[i])
		return (ft_exit(INV_ARG));
	if (ft_atol(str) == -1 || (!ft_atol(str) && n_arg != 5))
		return (ft_exit(INV_ARG));
	return (0);
}

char	**ft_parser(int ac, char **av)
{
	int i;
	
	if (ac != 5 && ac != 6)
	{
		ft_exit(PARAM_ERROR);
		return (NULL);	
	}
	i = 0;
	while (av[++i])
	{
		if (ft_checkint(av[i], i))
			return (NULL);
	}
	if (ac == 6 && ft_atol(av[5]) == 0)
		return (NULL);
	return (av);
}
