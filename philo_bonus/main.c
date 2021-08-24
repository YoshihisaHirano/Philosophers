/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:00:29 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:00:52 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	settings_init(t_settings *set)
{
	*set = (t_settings){0};
	set->must_eat = -1;
}

void	parse_args(t_settings *set, char **argv, int argc)
{
	int		i;
	int		args[5];

	i = 0;
	while (i < argc - 1 && i < 5)
	{
		args[i] = ft_atoi(argv[i + 1]);
		if (args[i] < 0 || args[0] == 0)
			error_exit(FORMAT_ISSUE, set, NULL);
		i++;
	}
	set->philo_no = args[0];
	set->die_time = args[1];
	set->eat_time = args[2];
	set->sleep_time = args[3];
	if (argc >= 6)
		set->must_eat = args[4];
}

t_philo	*create_philos(t_settings *set)
{
	t_philo	*philos;
	int		i;

	philos = malloc(set->philo_no * sizeof(t_philo));
	if (!philos)
		error_exit(MEM_ISSUE, NULL, NULL);
	i = 1;
	while (i <= set->philo_no)
	{
		philos[i - 1].id = i;
		philos[i - 1].meals_no = 0;
		philos[i - 1].set = set;
		i++;
	}
	set->philos = philos;
	return (philos);
}

int	main(int argc, char **argv)
{
	t_settings	set;
	t_philo		*philos;

	if (argc < 5)
	{
		printf("This program should have at least 4 arguments!\n");
		return (1);
	}
	settings_init(&set);
	parse_args(&set, argv, argc);
	sem_start(&set);
	philos = create_philos(&set);
	create_processes(&set, philos);
	sem_wait(set.sim_stop);
	kill_processes(&set, philos);
	close_sems(&set);
	return (0);
}
