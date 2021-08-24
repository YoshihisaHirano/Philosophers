/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:06:33 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:06:47 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_forks(t_settings *set)
{
	pthread_mutex_t	*forks;
	int				i;
	int				error;

	forks = malloc(sizeof(pthread_mutex_t) * set->thread_no);
	if (!forks)
	{
		printf("Memory allocation error\n");
		return (1);
	}
	i = 0;
	while (i < set->thread_no)
	{
		error = pthread_mutex_init(&forks[i], NULL);
		if (error)
		{
			printf("Mutex init error\n");
			free(forks);
			return (1);
		}
		i++;
	}
	set->forks = forks;
	return (0);
}

int	destroy_mutexes(t_settings *set)
{
	int	i;

	i = 0;
	while (i < set->thread_no)
	{
		pthread_mutex_destroy(&(set->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&set->print);
	free(set->forks);
	return (0);
}

int	create_timers(t_settings *set)
{
	t_timer	*timers;
	int		error;

	timers = malloc(sizeof(t_timer) * set->thread_no);
	if (!timers)
	{
		printf("Memory allocation error\n");
		return (1);
	}
	error = pthread_mutex_init(&set->print, NULL);
	if (error)
	{
		printf("Mutex init error\n");
		free(set->forks);
		free(timers);
		return (1);
	}
	set->timers = timers;
	return (0);
}
