/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:26:50 by aal-joul          #+#    #+#             */
/*   Updated: 2025/07/04 18:38:52 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	smart_sleep(t_philo	*philo, long duration)
{
	long	start;

	start = get_time_now();
	while ((get_time_now() - start) < duration)
	{
		if (is_simulation_over(philo->data))
			return (0);
		usleep(100);
	}
	return (1);
}

int	is_simulation_over(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_lock);
	result = data->someone_die;
	pthread_mutex_unlock(&data->death_lock);
	return (result);
}

int	has_died(t_philo *philo)
{
	long	now;
	long	last_meal;

	now = get_time_now();
	pthread_mutex_lock(&philo->state_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->state_lock);
	if (now - last_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death_lock);
		if (!philo->data->someone_die)
		{
			philo->data->someone_die = 1;
			pthread_mutex_lock(&philo->data->print_lock);
			printf("%ld %d died\n", now - philo->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->print_lock);
		}
		pthread_mutex_unlock(&philo->data->death_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!is_simulation_over(data))
	{
		i = 0;
		while (i < data->philo_n)
		{
			if (has_died(&data->philos[i]))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
