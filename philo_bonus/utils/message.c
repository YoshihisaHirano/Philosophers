/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:04:40 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:04:55 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	message(t_philo *p, char *code)
{
	struct timeval	t;
	char			*philo_no;
	char			*temp;

	if (!code)
	{
		sem_wait(p->set->print);
		gettimeofday(&t, NULL);
		printf("%d %d died\n", ms(t, p->set), p->id);
	}
	else
	{
		gettimeofday(&t, NULL);
		temp = ft_strjoin(ft_itoa(ms(t, p->set)), " ");
		philo_no = ft_strjoin(temp, ft_itoa(p->id));
		free(temp);
		temp = ft_strjoin(philo_no, code);
		free(philo_no);
		sem_wait(p->set->print);
		ft_putstr_fd(temp, 1);
		sem_post(p->set->print);
	}
}

void	error_exit(int code, t_settings *set, t_philo *philos)
{
	if (code == SEM_ISSUE)
		printf("Semaphore opening error\n");
	if (code == FORMAT_ISSUE)
		printf("Wrong format of the argument(s)\n");
	if (code == MEM_ISSUE)
		printf("Memory allocation error\n");
	if (code == PROC_ISSUE)
	{
		printf("Process creation error\n");
		kill_processes(set, philos);
	}
	if (code == THREAD_ISSUE)
	{
		printf("Thread creation error\n");
		kill_processes(set, philos);
	}
	exit(1);
}
