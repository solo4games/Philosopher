/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 12:40:57 by lbrandy           #+#    #+#             */
/*   Updated: 2021/07/27 16:17:50 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_glob
{
	struct timeval	start_t;
	pthread_t		t;
	pthread_mutex_t	*print;
	int				num;
	time_t			die_time;
	time_t			eat_time;
	time_t			sleep_time;
	int				eat_num;
}					t_glob;

typedef struct s_philo
{
	int				index;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		ph_thread;
	pthread_mutex_t	check_life_mutex;
	time_t			eat_t;
	int				eat_counter;
	t_glob			*glob;
}					t_philo;

size_t			ft_strlen(const char *s);
int				error_message(char *message, int ret);
int				pars_argv(char **argv, t_glob *glob, int flag);
int				fill_mass_forks(pthread_mutex_t *forks, int num);
int				fill_mass_philo(t_philo *philos, int num, t_glob *glob);
time_t			get_time(t_glob *glob);
int				my_usleep(suseconds_t time, t_glob *glob);
int				simulation(t_philo *philos);
int				think(t_philo *philo);
int				sleeping(t_philo *philo);
int				eat(t_philo *philo);
int				try_forks(t_philo *philo);
int				put_forks(t_philo *philo);
void			philo_death(t_philo *philo);
void			*start_thread(t_philo *philo);
int				print(char *str, t_philo *philo);

#endif
