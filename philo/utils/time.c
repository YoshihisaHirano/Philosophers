/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:10:39 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:11:01 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ms(struct timeval curr, t_settings *set)
{
	long int	now_ms;

	now_ms = (curr.tv_sec * (long)1000) + (curr.tv_usec / 1000);
	return ((int)(now_ms - set->start_time));
}

int	dead_time(struct timeval curr, t_settings *set, int i)
{
	long int		now_ms;
	long int		start_ms;
	struct timeval	start;
	t_philo			philo;

	philo = ((t_philo *)(set->philos))[i];
	start = philo.time;
	now_ms = (curr.tv_sec * (long)1000) + (curr.tv_usec / 1000);
	start_ms = (start.tv_sec * (long)1000) + (start.tv_usec / 1000);
	return ((int)(now_ms - start_ms));
}

void	set_timers(t_philo *phid)
{
	int				i;
	struct timeval	now;

	gettimeofday(&now, NULL);
	phid->set->start_time = (now.tv_sec * (long)1000) + (now.tv_usec / 1000);
	i = 0;
	while (i < phid->set->thread_no)
	{
		phid[i].time = now;
		i++;
	}
}
