/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:08:55 by aal-joul          #+#    #+#             */
/*   Updated: 2025/07/02 15:34:10 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	long		last_meal;
	int			meals_c;
	pthread_t	thread;
	t_data		*data;
	pthread_mutex_t	state_lock;
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
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
}	t_data;

int		check_death(t_philo *philo);
int		has_died(t_philo *philo);
int		eat(t_philo *philo);
int		take_forks(t_philo *philo);
int		is_simulation_over(t_data *data);
int		sleep_and_think(t_philo *philo);
int		ft_atoi(const char *str);
int		parse_args(t_data *data, int argc, char **argv);
int		smart_sleep(t_philo	*philo, long duration);
long	get_time_now(void);
void	print_state(t_philo *philo, const char *msg);
void	put_down_forks(t_philo *philo);
void	*all_feed(void *arg);
void	*routine(void *arg);
void	init_mutexes(t_data *data);
void	start_threads(t_data *data);
void	join_threads(t_data *data);
void	cleanup(t_data *data);
void	init_philo(t_data *data);
void	*monitor(void *arg);

#endif
