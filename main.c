/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:12 by aal-joul          #+#    #+#             */
/*   Updated: 2025/07/01 16:36:07 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("wrong number of input arguments\n");
		return (1);
	}
	data->philo_n = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->eat_count = -1;
	data->has_limit = 0;
	if (argc == 6)
	{
		data->eat_count = ft_atoi(argv[5]);
		data->has_limit = 1;
	}
	if (data->philo_n <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (data->has_limit && data->eat_count <= 0))
	{
		printf("invalid inputs\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(&data, argc, argv))
		return (1);
	init_mutexes(&data);
	init_philo(&data);
	start_threads(&data);
	if (data.philo_n == 1)
	{
		cleanup(&data);
		return (0);
	}
	join_threads(&data);
	cleanup(&data);
	return (0);
}
