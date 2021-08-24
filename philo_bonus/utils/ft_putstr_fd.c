/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:03:51 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:04:18 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

size_t	ft_strlen(char const *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		counter = counter + 1;
	}
	return (counter);
}

void	ft_putstr_fd(char const *str, int fd)
{
	size_t	len;

	if (!str || fd < 0)
		return ;
	len = ft_strlen(str);
	write(fd, str, len);
}
