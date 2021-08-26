/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_meals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 15:59:29 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:00:23 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*waiter_routine(void *args)
{
	t_settings		*set;
	int				i;
	struct timeval	now;

	set = (t_settings *)args;
	i = 0;
	while (i < set->philo_no)
	{
		sem_wait(set->all_ate);
		i++;
	}
	gettimeofday(&now, NULL);
	sem_wait(set->print);
	printf("%d Everyone is full (っ˘ڡ˘ς)\n", ms(now, set));
	sem_post(set->sim_stop);
	return (NULL);
}

void	check_meals(t_settings *set)
{
	pthread_t	waiter;
	int			error;

	error = pthread_create(&waiter, NULL, waiter_routine, set);
	if (error)
		error_exit(THREAD_ISSUE, set);
}
