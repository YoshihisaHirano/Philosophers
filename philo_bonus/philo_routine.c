/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:01:20 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:01:36 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->set->forks);
	message(philo, TAKE_FORK);
	sem_wait(philo->set->forks);
	philo->has_forks++;
	message(philo, TAKE_FORK);
	message(philo, EAT);
	philo->last_meal = get_time();
	ft_usleep(philo->set->eat_time);
	sem_post(philo->set->forks);
	sem_post(philo->set->forks);
	philo->has_forks--;
	if (philo->set->must_eat != -1)
		philo->meals_no++;
}

void	form_queue(t_philo *philo)
{
	if (philo->set->philo_no % 2 != 0 && philo->id % 2 != 0 && philo->id == 1)
	{
		message(philo, THINK);
		ft_usleep(philo->set->eat_time + (philo->set->eat_time / 4));
	}
	else if (philo->id % 2 == 0)
	{
		message(philo, THINK);
		ft_usleep(philo->set->eat_time);
	}
	else
		message(philo, THINK);
}

void	philo_routine(t_philo *philo)
{
	philo->started = 0;
	create_watcher(philo);
	sem_wait(philo->set->sim_start);
	philo->set->start_time = get_time();
	philo->last_meal = philo->set->start_time;
	philo->started = 1;
	form_queue(philo);
	while (1)
	{
		philo_eat(philo);
		if (philo->meals_no == philo->set->must_eat)
			sem_post(philo->set->all_ate);
		message(philo, SLEEP);
		ft_usleep(philo->set->sleep_time);
		message(philo, THINK);
	}
}
