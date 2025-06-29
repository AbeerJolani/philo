/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:09:40 by aal-joul          #+#    #+#             */
/*   Updated: 2025/06/29 16:51:28 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(&data, argc, argv))
		return (1);

	init_mutexes(&data);
	init_philos(&data);
	start_threads(&data);
	join_threads(&data);
	cleanup(&data);
	return (0);
}
