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

void	print_death(t_philo *p)
{
	struct timeval	t;

	sem_wait(p->set->print);
	gettimeofday(&t, NULL);
	printf("%d %d died\n", ms(t, p->set), p->id);
}

void	message(t_philo *p, char *code)
{
	struct timeval	t;
	char			*temp;
	char			*temp2;
	char			*str_id;
	char			*str_ms;

	if (!code)
		print_death(p);
	else
	{
		gettimeofday(&t, NULL);
		str_ms = ft_itoa(ms(t, p->set));
		str_id = ft_itoa(p->id);
		temp = ft_strjoin(str_ms, " ");
		temp2 = ft_strjoin(temp, str_id);
		free(temp);
		temp = ft_strjoin(temp2, code);
		free(temp2);
		sem_wait(p->set->print);
		ft_putstr_fd(temp, 1);
		sem_post(p->set->print);
		free(temp);
		free(str_id);
		free(str_ms);
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
