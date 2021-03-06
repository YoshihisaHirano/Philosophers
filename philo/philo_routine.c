/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:06:58 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:07:19 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	forming_queue(t_philo *th)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (th->set->thread_no % 2 != 0 && th->id % 2 != 0 && th->id == 1)
	{
		message(THINK, now, th, 0);
		ft_usleep(th->set->eat_time);
		if (th->stop)
			return ;
		ft_usleep(th->set->eat_time / 4);
	}
	else if (th->id % 2 == 0)
		message(THINK, now, th, 0);
	else
	{
		message(THINK, now, th, 0);
		ft_usleep(th->set->eat_time);
	}
}

int	take_forks(t_philo *th, int left_idx, int right_idx)
{
	struct timeval	now;

	if (th->set->forks && !th->stop)
	{
		pthread_mutex_lock(&th->set->forks[right_idx]);
		gettimeofday(&now, NULL);
		if (th->stop)
			return (1);
		message(TAKE_FORK, now, th, 0);
	}
	if (th->set->forks && !th->stop)
	{
		pthread_mutex_lock(&th->set->forks[left_idx]);
		pthread_mutex_lock(&th->death_mutex);
		gettimeofday(&now, NULL);
		if (th->stop)
			return (1);
		message(TAKE_FORK, now, th, 0);
	}
	return (0);
}

int	release_forks(t_philo *th, int left_idx, int right_idx)
{
	struct timeval	now;

	if (th->set->forks && !th->stop)
	{
		pthread_mutex_unlock(&th->set->forks[left_idx]);
		gettimeofday(&now, NULL);
		if (th->stop)
			return (1);
	}
	if (th->set->forks && !th->stop)
	{
		pthread_mutex_unlock(&th->set->forks[right_idx]);
		gettimeofday(&now, NULL);
		if (th->stop)
			return (1);
	}
	return (0);
}

void	eating_routine(t_philo *th)
{
	int				left_fork;
	int				right_fork;
	struct timeval	now;

	left_fork = th->id - 1;
	right_fork = th->id;
	if (th->id == th->set->thread_no)
		right_fork = 0;
	if (take_forks(th, left_fork, right_fork) > 0)
		return ;
	gettimeofday(&now, NULL);
	change_status(1, now, th);
	if (th->stop)
		return ;
	message(EAT, now, th, 0);
	pthread_mutex_unlock(&th->death_mutex);
	ft_usleep(th->set->eat_time);
	change_status(2, now, th);
	if (release_forks(th, left_fork, right_fork) > 0)
		return ;
}

void	*philo_routine(void *args)
{
	struct timeval	now;
	t_philo			*me;

	me = (t_philo *)args;
	gettimeofday(&now, NULL);
	forming_queue(me);
	while (!me->stop)
	{
		eating_routine(me);
		gettimeofday(&now, NULL);
		if (me->stop)
			break ;
		message(SLEEP, now, me, 0);
		if (me->stop)
			break ;
		ft_usleep(me->set->sleep_time);
		if (me->stop)
			break ;
		gettimeofday(&now, NULL);
		if (me->stop)
			break ;
		message(THINK, now, me, 0);
	}
	return (NULL);
}
