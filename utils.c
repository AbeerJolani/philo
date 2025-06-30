/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:09:28 by aal-joul          #+#    #+#             */
/*   Updated: 2025/06/30 12:57:47 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_n);
	if (!data->forks)
		exit(1);
	while (i < data->philo_n)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_lock, NULL);
}
void	start_threads(t_data *data)
{
	int	i;

	data->start_time = get_time_now();
	data->someone_die = 0;
	i = 0;
	while (i < data->philo_n)
	{
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
		i++;
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	free(data->forks);
	free(data->philos);
}
