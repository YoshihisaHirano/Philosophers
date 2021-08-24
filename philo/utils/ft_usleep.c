/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:09:58 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:10:17 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long int	get_time(void)
{
	struct timeval	time;
	long int		res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * (long)1000) + (time.tv_usec / 1000);
	return (res);
}

void	ft_usleep(int time)
{
	long int	start;

	start = get_time();
	while (get_time() < start + time)
		usleep(1000);
}
