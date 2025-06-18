/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:09:40 by aal-joul          #+#    #+#             */
/*   Updated: 2025/06/18 17:52:57 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_argu	argu;
	
	if (!parse_ar(argc, argv, argu))
	{
		printf("ERROR: INVALID ARGUMENTS\n");
		return (1);
	}
	printf("philosophers num: %d\n", argu.philo_n);
	printf("time_to_die: %d\n", argu.time_to_die);
	printf("time_to_eat: %d\n", argu.time_to_eat);
	printf("time_to_sleep: %d\n", argu.time_to_sleep);
	if (argu.has_limit)
		printf("must eat: %d times\n", argu.eat_count);
	else
		printf("No eat limit set\n");
	return (0);
}
