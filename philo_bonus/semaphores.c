/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:01:58 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:02:19 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sem_setup(t_settings *set)
{
	int	i;

	i = -1;
	while (++i < set->philo_no)
		sem_wait(set->sim_start);
	i = -1;
	while (++i < set->philo_no)
		sem_wait(set->exit_sig);
	sem_wait(set->sim_stop);
	sem_wait(set->all_ate);
}

void	sem_start(t_settings *st)
{
	sem_unlink("forks");
	st->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, st->philo_no);
	if (st->forks == SEM_FAILED)
		error_exit(SEM_ISSUE, st, NULL);
	sem_unlink("sim_stop");
	st->sim_stop = sem_open("sim_stop", O_CREAT | O_EXCL, 0644, 1);
	if (st->sim_stop == SEM_FAILED)
		error_exit(SEM_ISSUE, st, NULL);
	sem_unlink("print");
	st->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	if (st->print == SEM_FAILED)
		error_exit(SEM_ISSUE, st, NULL);
	sem_unlink("sim_start");
	st->sim_start = sem_open("sim_start", O_CREAT | O_EXCL, 0644, st->philo_no);
	if (st->print == SEM_FAILED)
		error_exit(SEM_ISSUE, st, NULL);
	sem_unlink("all_ate");
	st->all_ate = sem_open("all_ate", O_CREAT | O_EXCL, 0644, 1);
	if (st->all_ate == SEM_FAILED)
		error_exit(SEM_ISSUE, st, NULL);
	sem_unlink("exit_sig");
	st->exit_sig = sem_open("exit_sig", O_CREAT | O_EXCL, 0644, st->philo_no);
	if (st->exit_sig == SEM_FAILED)
		error_exit(SEM_ISSUE, st, NULL);
	sem_setup(st);
}

void	close_sems(t_settings *set)
{
	sem_close(set->exit_sig);
	sem_close(set->forks);
	sem_close(set->print);
	sem_close(set->all_ate);
	sem_close(set->sim_stop);
	sem_close(set->sim_start);
}
