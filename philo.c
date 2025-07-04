/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:08:47 by aal-joul          #+#    #+#             */
/*   Updated: 2025/07/04 18:48:59 by aal-joul         ###   ########.fr       */
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
		pthread_mutex_init(&data->philos[i].state_lock, NULL);
		i++;
	}
}

int	check_death(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->death_lock);
	dead = philo->data->someone_die;
	pthread_mutex_unlock(&philo->data->death_lock);
	return (dead);
}

int	sleep_and_think(t_philo *philo)
{
	int	s;

	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->someone_die)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	print_state(philo, "is sleeping");
	s = smart_sleep(philo, philo->data->time_to_sleep);
	return (s);
}

int	execute_loop(t_philo *philo)
{
	while (1)
	{
		if (check_death(philo))
			break ;
		print_state(philo, "is thinking");
		if (!take_forks(philo))
			break ;
		if (!eat(philo))
		{
			put_down_forks(philo);
			break ;
		}
		put_down_forks(philo);
		if (!sleep_and_think(philo))
			break ;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(1000);
	execute_loop(philo);
	return (NULL);
}
