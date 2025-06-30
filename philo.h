/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:08:55 by aal-joul          #+#    #+#             */
/*   Updated: 2025/06/30 13:29:21 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	long		last_meal;
	int			meals_c;
	pthread_t	thread;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	int				philo_n;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				has_limit;
	int				someone_die;
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_lock;
}	t_data;

int		parse_args(t_data *data, int argc, char **argv);
void	*routine(void *arg);
void	init_mutexes(t_data *data);
void	start_threads(t_data *data);
void	join_threads(t_data *data);
void	cleanup(t_data *data);
void	init_philo(t_data *data);

#endif
