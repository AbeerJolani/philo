/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:19:51 by aal-joul          #+#    #+#             */
/*   Updated: 2025/07/02 17:40:45 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, const char *msg)
{
	long	time;
	if (check_death(philo))
		return ;
	time = get_time_now() - philo->data->start_time;
	printf("%ld %d %s\n", time, philo->id, msg);
}

int take_one_fork(t_philo *philo, int fork_id, const char *side)
{
	pthread_mutex_lock(&philo->data->forks[fork_id]);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[fork_id]);
		return (0);
	}
	pthread_mutex_lock(&philo->data->print_lock);
	print_state(philo, side);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (1);
}

int	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;
	const char *first_msg;
	const char *second_msg;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
		first_msg = "has taken left fork";
		second_msg = "has taken right fork";
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
		first_msg = "has taken right fork";
		second_msg = "has taken left fork";
	}
	if (!take_one_fork(philo, first_fork, first_msg))
		return (0);
	if (!take_one_fork(philo, second_fork, second_msg))
	{
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return (0);
	}
	return (1);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_lock);
	philo->last_meal = get_time_now();
	pthread_mutex_unlock(&philo->state_lock);

	pthread_mutex_lock(&philo->data->print_lock);
	print_state(philo, "is eating");
	pthread_mutex_unlock(&philo->data->print_lock);
	if (!smart_sleep(philo, philo->data->time_to_eat))
		return (0);
	pthread_mutex_lock(&philo->state_lock);
	philo->meals_c++;
	pthread_mutex_unlock(&philo->state_lock);
	return (!check_death(philo));
}


void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}
