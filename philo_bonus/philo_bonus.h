/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:00:58 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:01:16 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>
# define SEM_ISSUE 1
# define PROC_ISSUE 2
# define THREAD_ISSUE 4
# define FORMAT_ISSUE 5
# define EAT " is eating\n"
# define THINK " is thinking\n"
# define TAKE_FORK " has taken a fork\n"
# define SLEEP " is sleeping\n"
# define DEATH NULL

typedef struct s_settings
{
	int				philo_no;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	long int		start_time;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*sim_stop;
	sem_t			*sim_start;
	sem_t			*all_ate;
	sem_t			*exit_sig;
	void			*philos;
}	t_settings;

typedef struct s_philo
{
	int				id;
	int				meals_no;
	long int		last_meal;
	t_settings		*set;
	int				started;
	sem_t			*death;
}	t_philo;

int			ft_atoi(const char *nptr);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_putstr_fd(char const *str, int fd);
char		*ft_itoa(int n);
size_t		ft_strlen(char const *str);
void		ft_usleep(int time);
void		message(t_philo *philo, char *code);
long int	get_time(void);
int			ms(struct timeval curr, t_settings *set);
void		error_exit(int code, t_settings *set);
void		sem_start(t_settings *set);
void		start_philo_sem(t_philo *philo);
void		kill_processes(t_settings *set);
void		create_processes(t_settings *set, t_philo *philos);
void		check_meals(t_settings *set);
void		philo_routine(t_philo philo);
void		create_watcher(t_philo *philo);
void		close_sems(t_settings *set);

#endif
