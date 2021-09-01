/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <aalannys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:07:22 by aalannys          #+#    #+#             */
/*   Updated: 2021/08/24 16:07:38 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# define EAT " is eating\n"
# define THINK " is thinking\n"
# define SLEEP " is sleeping\n"
# define TAKE_FORK " has taken a fork\n"
# define DIED " died\n"

typedef struct s_settings
{
	int				thread_no;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	pthread_mutex_t	*forks;
	long int		start_time;
	pthread_mutex_t	print;
	void			*philos;
}	t_settings;

typedef struct s_philo
{
	t_settings		*set;
	int				id;
	int				stop;
	struct timeval	time;
	int				meals_no;
	pthread_mutex_t	death_mutex;
}	t_philo;

int		ft_atoi(const char *nptr);
int		start_threads(t_settings *set);
int		create_forks(t_settings *set);
void	*philo_routine(void *arg);
int		free_memory(t_settings *set, pthread_t *philo, t_philo *id, int *res);
void	*watcher_routine(void *arg);
void	finish_threads(pthread_t *philos, t_settings *set);
int		ms(struct timeval curr, t_settings *set);
int		dead_time(struct timeval curr, t_settings *set, int i);
void	set_timers(t_philo *philos_id);
int		destroy_mutexes(t_settings *set);
int		initialize_mutex(pthread_mutex_t *mx);
void	ft_usleep(int time);
void	change_status(int code, struct timeval now, t_philo *th);
void	message(char *code, struct timeval now, t_philo *th, int flag);
void	ft_putstr_fd(char const *str, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
size_t	ft_strlen(char const *str);

#endif
