/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:07:40 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:07:57 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_philo_id(t_settings *set)
{
	t_philo	*philo_id;
	int		i;

	philo_id = malloc(sizeof(t_philo) * set->thread_no);
	if (!philo_id)
	{
		printf("Memory allocation error\n");
		return (NULL);
	}
	i = 1;
	while (i <= set->thread_no)
	{
		philo_id[i - 1].set = set;
		philo_id[i - 1].id = i;
		philo_id[i - 1].stop = 0;
		i++;
	}
	set->philos = philo_id;
	return (philo_id);
}

pthread_t	*create_philo_arr(int qty)
{
	pthread_t	*philos;

	philos = malloc(sizeof(pthread_t) * (qty + 1));
	if (!philos)
	{
		printf("Memory allocation error\n");
		return (NULL);
	}
	return (philos);
}

int	create_threads(pthread_t *philos, t_settings *set, t_philo *ids)
{
	int	i;
	int	error;

	i = 1;
	while (i <= set->thread_no)
	{
		error = pthread_create(&philos[i], NULL, philo_routine, &ids[i - 1]);
		if (error)
		{
			printf("Thread creation error\n");
			free_memory(set, philos, ids, NULL);
			return (1);
		}
		i++;
	}
	error = pthread_create(&philos[0], NULL, watcher_routine, set);
	if (error)
	{
		printf("Thread creation error\n");
		free_memory(set, philos, ids, NULL);
		return (1);
	}
	return (0);
}

int	join_threads(pthread_t *philos, t_settings *set, t_philo *ids)
{
	int	i;
	int	error;
	int	jerror;
	int	*res;

	i = 0;
	while (i < set->thread_no + 1)
	{
		jerror = pthread_join(philos[i], (void **)&res);
		if (jerror)
		{
			printf("Thread join error\n");
			break ;
		}
		if (res)
		{
			finish_threads(philos, set);
			break ;
		}
		i++;
	}
	error = free_memory(set, philos, ids, res);
	if (error || jerror)
		return (1);
	return (0);
}

int	start_threads(t_settings *set)
{
	pthread_t	*philos;
	t_philo		*id;
	int			output;

	philos = create_philo_arr(set->thread_no);
	if (!philos)
		return (1);
	id = create_philo_id(set);
	if (!id)
		return (1);
	set_timers(set);
	output = create_threads(philos, set, id);
	if (output)
		return (1);
	output = join_threads(philos, set, id);
	return (output);
}
