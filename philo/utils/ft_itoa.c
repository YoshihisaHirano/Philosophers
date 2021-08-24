/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:09:01 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:09:17 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	*start;
	char	temp;

	start = str;
	len = 0;
	i = 0;
	while (*str)
	{
		len++;
		str++;
	}
	str--;
	while (i < (len / 2))
	{
		temp = start[i];
		start[i] = (*str);
		start[len - 1 - i] = temp;
		i++;
		str--;
	}
	return (start);
}

static	size_t	find_num_len(int num)
{
	size_t	str_size;

	str_size = 0;
	if (num <= 0)
		str_size++;
	while (num != 0)
	{
		str_size++;
		num /= 10;
	}
	return (str_size);
}

char	*ft_itoa(int n)
{
	char			*result;
	char			*start;
	size_t			len;
	unsigned int	u_n;

	len = find_num_len(n) + 1;
	result = malloc(len);
	if (!result)
		return (NULL);
	start = result;
	result[len - 1] = '\0';
	if (n == 0)
		result[0] = '0';
	u_n = n;
	if (n < 0)
	{
		u_n = n * (-1);
		result[len - 2] = '-';
	}
	while (u_n != 0)
	{
		*result++ = (u_n % 10) + '0';
		u_n /= 10;
	}
	return (ft_strrev(start));
}
