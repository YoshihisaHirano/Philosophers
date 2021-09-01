/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:01:39 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:01:55 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_sig(t_settings *set)
{
	int	i;

	i = -1;
	while (++i < set->philo_no)
		sem_post(set->sim_start);
	set->start_time = get_time();
}

void	create_processes(t_settings *set, t_philo *philos)
{
	int		i;
	int		pid;

	i = -1;
	if (set->must_eat != -1)
		check_meals(set);
	while (++i < set->philo_no)
	{
		pid = fork();
		if (pid < 0)
			error_exit(PROC_ISSUE, set);
		else if (pid == 0)
			philo_routine(philos[i]);
	}
	ft_usleep(set->philo_no * 10);
	start_sig(set);
}

void	kill_processes(t_settings *set)
{
	int	i;

	i = -1;
	while (++i < set->philo_no)
		sem_post(set->exit_sig);
	usleep(500);
}
