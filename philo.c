/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:08:47 by aal-joul          #+#    #+#             */
/*   Updated: 2025/06/29 16:40:02 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_n);
	if (!data->philos)
		exit(1);
	i = 0;
	while (i < data->philo_n)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philo_n;
		data->philos[i].meals_c = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		i++;
	}
}
