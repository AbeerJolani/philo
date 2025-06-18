/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:09:28 by aal-joul          #+#    #+#             */
/*   Updated: 2025/06/18 17:52:17 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *nptr)
{
	int		i;
	long long	n;

	n = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		return (-1);
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10) + (nptr[i] - '0');
		if (n > 2147483647)
			return (-1);
		i++;
	}
	return ((int)n);
}
int	parse_ar(int a, char **v, t_argu *g)
{
	int	i;

	i = 1;
	if (a != 5 || a != 6)
		return (0);
	while (i < a)
	{
		if (ft_atoi(v[i] == -1))
			return (0);
			i++;
	}
	g->philo_n = ft_atoi(v[1]);
	g->time_to_die = ft_atoi(v[2]);
	g->time_to_eat = ft_atoi(v[3]);
	g->time_to_sleep = ft_atoi(v[4]);

}
