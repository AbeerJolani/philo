/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:35:52 by aal-joul          #+#    #+#             */
/*   Updated: 2025/07/01 16:37:24 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_data *data)
{
	printf("0 1 is thinking\n");
	printf("0 1 has taken left fork\n");
	smart_sleep(data->time_to_die);
	printf("%d 1 died\n", data->time_to_die);
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
