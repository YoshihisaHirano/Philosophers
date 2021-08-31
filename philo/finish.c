/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:05:57 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:06:13 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_memory(t_settings *set, pthread_t *philo, t_philo *ids, int *res)
{
	int	error;

	error = destroy_mutexes(set);
	if (philo)
		free(philo);
	if (ids)
		free(ids);
	if (res)
		free(res);
	return (error);
}

void	finish_threads(pthread_t *philos, t_settings *set)
{
	int	i;

	i = 0;
	while (i < set->thread_no)
	{
		pthread_detach(philos[i]);
		i++;
	}
	usleep(500);
}
