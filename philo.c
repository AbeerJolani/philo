/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:08:47 by aal-joul          #+#    #+#             */
/*   Updated: 2025/07/01 16:33:24 by aal-joul         ###   ########.fr       */
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

int	sleep_and_think(t_philo *philo)
{
	if (check_death(philo))
		return (0);
	print_state(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(200);
	while (!check_death(philo))
	{
		print_state(philo, "is thinking");
		if (!take_forks(philo))
			break ;
		if (!eat(philo))
			break ;
		put_down_forks(philo);
		if (!sleep_and_think(philo))
			break ;
	}
	return (NULL);
}
