/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 13:04:59 by lbrandy           #+#    #+#             */
/*   Updated: 2021/07/27 16:06:19 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_death(t_philo *philo)
{
	print("died", philo);
}

int	print(char *str, t_philo *philo)
{
	time_t	t;

	t = get_time(philo->glob);
	if (pthread_mutex_lock(philo->glob->print) != 0)
		return (-1);
	printf("%ld %d %s\n", t, philo->index, str);
	if (pthread_mutex_unlock(philo->glob->print) != 0)
		return (-1);
	return (0);
}

int	my_usleep(suseconds_t time, t_glob *glob)
{
	time_t	time_fin;

	time_fin = get_time(glob) + time / 1000;
	if (time_fin == time - 1)
		return (-1);
	while (get_time(glob) < time_fin)
		usleep(100);
	return (0);
}

time_t	get_time(t_glob *glob)
{
	struct timeval	tv;
	time_t			tmp_s;
	suseconds_t		tmp_sus;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	tmp_s = tv.tv_sec - glob->start_t.tv_sec;
	tmp_sus = tv.tv_usec - glob->start_t.tv_usec;
	if (tmp_sus < 0)
	{
		tmp_s--;
		tmp_sus += 1000000;
	}
	return (tmp_s * 1000 + tmp_sus / 1000);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
