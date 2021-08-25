/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:02:22 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:02:42 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_check(void *args)
{
	t_philo			*philo;
	struct timeval	now;
	long int		ms_time;

	philo = (t_philo *)args;
	while (1)
	{
		if (philo->started)
		{
			gettimeofday(&now, NULL);
			ms_time = (now.tv_sec * (long)1000) + (now.tv_usec / 1000);
			if (ms_time - philo->last_meal > philo->set->die_time
				&& !philo->has_forks)
			{
				message(philo, DEATH);
				break ;
			}
		}
	}
	sem_post(philo->set->sim_stop);
	return (NULL);
}

void	*exit_check(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	sem_wait(philo->set->exit_sig);
	free(philo->set->philos);
	exit(0);
}

void	create_watcher(t_philo *philo)
{
	pthread_t	death_watcher;
	pthread_t	exit_watcher;
	int			error;

	error = pthread_create(&death_watcher, NULL, death_check, philo);
	if (error)
	{
		free(philo->set->philos);
		error_exit(THREAD_ISSUE, philo->set, philo->set->philos);
	}
	error = pthread_create(&exit_watcher, NULL, exit_check, philo);
	if (error)
	{
		free(philo->set->philos);
		pthread_detach(death_watcher);
		error_exit(THREAD_ISSUE, philo->set, philo->set->philos);
	}
}
