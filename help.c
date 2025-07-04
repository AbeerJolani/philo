/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:19:51 by aal-joul          #+#    #+#             */
/*   Updated: 2025/07/04 19:00:01 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, const char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->someone_die)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	time = get_time_now() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}

int	take_one_fork(t_philo *philo, int fork_id, const char *side)
{
	pthread_mutex_lock(&philo->data->forks[fork_id]);
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->someone_die)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		pthread_mutex_unlock(&philo->data->forks[fork_id]);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	print_state(philo, side);
	return (1);
}

static t_fork_order	get_fork_order(t_philo *philo)
{
	t_fork_order	order;

	if (philo->id % 2 == 0)
	{
		order.first = philo->left_fork;
		order.second = philo->right_fork;
		order.first_msg = "has taken left fork";
		order.second_msg = "has taken right fork";
	}
	else
	{
		order.first = philo->right_fork;
		order.second = philo->left_fork;
		order.first_msg = "has taken right fork";
		order.second_msg = "has taken left fork";
	}
	return (order);
}

int	take_forks(t_philo *philo)
{
	t_fork_order	order;

	order = get_fork_order(philo);
	if (!take_one_fork(philo, order.first, order.first_msg))
		return (0);
	if (!take_one_fork(philo, order.second, order.second_msg))
	{
		pthread_mutex_unlock(&philo->data->forks[order.first]);
		return (0);
	}
	return (1);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_lock);
	philo->last_meal = get_time_now();
	pthread_mutex_unlock(&philo->state_lock);
	print_state(philo, "is eating");
	if (!smart_sleep(philo, philo->data->time_to_eat))
		return (0);
	pthread_mutex_lock(&philo->state_lock);
	philo->meals_c++;
	pthread_mutex_unlock(&philo->state_lock);
	return (1);
}
