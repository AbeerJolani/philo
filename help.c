/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:19:51 by aal-joul          #+#    #+#             */
/*   Updated: 2025/07/01 16:38:37 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->death_lock);
	dead = philo->data->someone_die;
	pthread_mutex_unlock(&philo->data->death_lock);
	return (dead);
}

void	print_state(t_philo *philo, const char *msg)
{
	long	time;

	time = get_time_now() - philo->data->start_time;
	printf("%ld %d %s\n", time, philo->id, msg);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	if (check_death(philo))
		return (pthread_mutex_unlock(&philo->data->forks[philo->left_fork]), 0);
	print_state(philo, "has taken left fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (0);
	}
	print_state(philo, "has taken right fork");
	return (1);
}

int	eat(t_philo *philo)
{
	philo->last_meal = get_time_now();
	print_state(philo, "is eating");
	smart_sleep(philo->data->time_to_eat);
	philo->meals_c++;
	return (!check_death(philo));
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}
