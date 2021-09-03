/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:06:16 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:06:30 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	settings_init(t_settings *set)
{
	*set = (t_settings){0};
	set->must_eat = -1;
	initialize_mutex(&set->print);
}

int	parse_args(t_settings *set, char **argv, int argc)
{
	int		i;
	int		args[5];

	i = 0;
	while (i < argc - 1 && i < 5)
	{
		args[i] = ft_atoi(argv[i + 1]);
		if (args[i] <= 0 || args[0] == 0)
		{
			printf("Wrong format of the argument no. %d\n", i + 1);
			return (1);
		}
		i++;
	}
	set->thread_no = args[0];
	set->die_time = args[1];
	set->eat_time = args[2];
	set->sleep_time = args[3];
	if (argc >= 6)
		set->must_eat = args[4];
	if (create_forks(set) > 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_settings	set;
	int			output;

	settings_init(&set);
	if (argc < 5)
	{
		printf("This program should have at least 4 arguments!\n");
		return (1);
	}
	output = parse_args(&set, argv, argc);
	if (output > 0)
		return (1);
	output = start_threads(&set);
	if (output > 0)
		return (1);
	return (0);
}
