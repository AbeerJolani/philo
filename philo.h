/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:08:55 by aal-joul          #+#    #+#             */
/*   Updated: 2025/06/18 17:52:11 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_args
{
	int	philo_n;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_count;
	int	has_limit;
}	t_argu;

int	parse_ar(int a, char **v, t_argu g);

#endif
