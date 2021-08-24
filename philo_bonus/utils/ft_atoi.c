/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:03:15 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:03:30 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	ft_isspace(int c)
{
	if (c == '\r' || c == '\f' || c == '\t' || c == '\v'
		|| c == ' ' || c == '\n')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

static unsigned long long	str_to_num(const char *start)
{
	unsigned long long	res;
	unsigned long long	rank;

	res = 0;
	rank = 1;
	while (ft_isdigit(*start))
		start++;
	if (!ft_isdigit(*start) && !ft_isspace(*start) && *start)
		return (-1);
	start--;
	while (ft_isdigit(*start))
	{
		res += (*start - '0') * rank;
		rank *= 10;
		start--;
	}
	return (res);
}

int	ft_atoi(const char *nptr)
{
	int					is_minus;
	unsigned long long	res;

	if (!(*nptr))
		return (0);
	is_minus = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			is_minus = -1;
		nptr++;
	}
	res = str_to_num(nptr);
	if (res < 0 || is_minus == -1)
		return (-1);
	return ((int)(res));
}
