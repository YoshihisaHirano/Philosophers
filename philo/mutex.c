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
			destroy_mutexes(set);
			free(forks);
			return (1);
		}
		i++;
	}
	set->forks = forks;
	return (0);
}

int	initialize_mutex(pthread_mutex_t *mx)
{
	int	error;

	error = pthread_mutex_init(mx, NULL);
	if (error)
	{
		printf("Mutex init error\n");
		return (1);
	}
	return (0);
}

int	destroy_mutexes(t_settings *set)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)(set->philos);
	while (i < set->thread_no)
	{
		pthread_mutex_destroy(&(set->forks[i]));
		pthread_mutex_destroy(&(philos[i].death_mutex));
		i++;
	}
	pthread_mutex_destroy(&set->print);
	free(set->forks);
	return (0);
}
