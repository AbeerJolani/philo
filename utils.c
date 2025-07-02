/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:09:28 by aal-joul          #+#    #+#             */
/*   Updated: 2025/07/02 16:20:07 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_now(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (result * sign);
}

// static int	all_philos_ate(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->philo_n)
// 	{
// 		if (data->philos[i].meals_c < data->eat_count)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

void *all_feed(void *arg)
{
	t_data *data = (t_data *)arg;
	int	i;
	int	full;

	while (!check_death(data->philos))
	{
		full = 0;
		i = 0;
		while (i < data->philo_n)
		{
			pthread_mutex_lock(&data->philos[i].state_lock);
			if (data->philos[i].meals_c >= data->eat_count)
				full++;
			pthread_mutex_unlock(&data->philos[i].state_lock);
			i++;
		}
		if (full == data->philo_n)
		{
			pthread_mutex_lock(&data->death_lock);
			data->someone_die = 1;
			pthread_mutex_unlock(&data->death_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
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
	pthread_mutex_destroy(&data->death_lock);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}
