/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:10:20 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:10:36 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	change_status(int code, struct timeval now, t_philo *th)
{
	if (code == 1)
		th->time = now;
	else if (code == 2)
		th->meals_no++;
}

void	message(char *code, struct timeval now, t_philo *th, int flag)
{
	char	*temp2;
	char	*temp;
	char	*str_id;
	char	*str_ms;

	(void)flag;
	str_id = ft_itoa(th->id);
	str_ms = ft_itoa(ms(now, th->set));
	temp = ft_strjoin(str_ms, " ");
	temp2 = ft_strjoin(temp, str_id);
	free(temp);
	temp = ft_strjoin(temp2, code);
	free(temp2);
	pthread_mutex_lock(&th->set->print);
	ft_putstr_fd(temp, 1);
	pthread_mutex_unlock(&th->set->print);
	free(temp);
	free(str_ms);
	free(str_id);
}
