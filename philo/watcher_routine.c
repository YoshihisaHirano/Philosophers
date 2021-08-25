/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:08:00 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:08:26 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_meals(t_settings *set)
{
	int				res;
	int				i;
	struct timeval	curr_time;

	res = 0;
	i = 0;
	if (set->must_eat == -1)
		return (0);
	while (i < set->thread_no)
	{
		if ((set->timers[i]).meals_no >= set->must_eat)
			res++;
		i++;
	}
	if (res == set->thread_no)
	{
		pthread_mutex_lock(&set->print);
		gettimeofday(&curr_time, NULL);
		printf("%d Everyone is full (っ˘ڡ˘ς)\n", ms(curr_time, set));
		return (1);
	}
	return (0);
}

int	check_death(t_settings *set)
{
	int				i;
	struct timeval	curr_time;

	i = 0;
	while (i < set->thread_no)
	{
		gettimeofday(&curr_time, NULL);
		if (dead_time(curr_time, set, i) > (set->die_time)
			&& !set->timers[i].has_forks)
		{
			pthread_mutex_lock(&set->print);
			printf("%d %d died\n", ms(curr_time, set),
				   i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*watcher_routine(void *arg)
{
	t_settings	*set;
	int			*i_ptr;
	int			i;
	t_philo		*philos;

	set = (t_settings *)arg;
	i_ptr = malloc(sizeof(int));
	while (1)
	{
		if (check_death(set) || check_meals(set))
		{
			*i_ptr = 1;
			i = 0;
			philos = (t_philo *)set->philos;
			while (i < set->thread_no)
			{
				philos[i].stop = 1;
				i++;
			}
			return (i_ptr);
		}
	}
}
