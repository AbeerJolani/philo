/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:35:52 by aal-joul          #+#    #+#             */
/*   Updated: 2025/07/02 12:00:31 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_data *data)
{
	t_philo	philo;

	philo.id = 1;
	philo.data = data;
	pthread_mutex_lock(&data->print_lock);
	printf("0 1 is thinking\n");
	printf("0 1 has taken left fork\n");
	pthread_mutex_unlock(&data->print_lock);
	smart_sleep(&philo, data->time_to_die);
	pthread_mutex_lock(&data->print_lock);
	printf("%d 1 died\n", data->time_to_die);
	pthread_mutex_unlock(&data->print_lock);
	pthread_mutex_lock(&data->death_lock);
	data->someone_die = 1;
	pthread_mutex_unlock(&data->death_lock);
}

void	start_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_th;
	pthread_t	all_feed_th;

	i = 0;
	data->start_time = get_time_now();
	data->someone_die = 0;
	if (data->philo_n == 1)
	{
		one_philo(data);
		return ;
	}
	while (i < data->philo_n)
	{
		data->philos[i].last_meal = data->start_time;
		pthread_create(&data->philos[i].thread, NULL, routine,
			&data->philos[i]);
		i++;
	}
	pthread_create(&monitor_th, NULL, monitor, data);
	if (data->has_limit)
		pthread_create(&all_feed_th, NULL, all_feed, data);
	pthread_join(monitor_th, NULL);
	if (data->has_limit)
		pthread_join(all_feed_th, NULL);
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
