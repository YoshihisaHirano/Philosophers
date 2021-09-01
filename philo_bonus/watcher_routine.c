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
	long int		death_timer;

	philo = (t_philo *)args;
	while (1)
	{
		if (philo->started)
		{
			gettimeofday(&now, NULL);
			ms_time = (now.tv_sec * (long)1000) + (now.tv_usec / 1000);
			sem_wait(philo->death);
			death_timer = philo->last_meal;
			sem_post(philo->death);
			if (ms_time - death_timer > philo->set->die_time)
			{
				message(philo, DEATH);
				break ;
			}
		}
		usleep(10);
	}
	sem_post(philo->set->sim_stop);
	return (NULL);
}

void	*exit_check(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	sem_wait(philo->set->exit_sig);
	sem_close(philo->death);
	exit(0);
}

void	create_watcher(t_philo *philo)
{
	pthread_t	death_watcher;
	pthread_t	exit_watcher;
	int			error;

	start_philo_sem(philo);
	error = pthread_create(&death_watcher, NULL, death_check, philo);
	if (error)
		error_exit(THREAD_ISSUE, philo->set);
	error = pthread_create(&exit_watcher, NULL, exit_check, philo);
	if (error)
		error_exit(THREAD_ISSUE, philo->set);
}
