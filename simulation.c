/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 16:06:00 by lbrandy           #+#    #+#             */
/*   Updated: 2021/07/27 16:17:18 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*free_all(t_philo *philos)
{
	int	i;
	int	count;

	i = 0;
	count = philos[0].glob->num;
	while (i < count)
	{
		pthread_mutex_destroy(philos[i].glob->print);
		pthread_mutex_destroy(philos[i].l_fork);
		pthread_mutex_destroy(&(philos[i].check_life_mutex));
		i++;
	}
	free(philos);
	return (NULL);
}

static int	check_eat_all(t_philo *philos)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (i < philos[0].glob->num)
	{
		if (philos[i].eat_counter >= philos[0].glob->eat_num
			&& philos[0].glob->eat_num != -1)
			res++;
		i++;
	}
	if (res == philos[0].glob->num)
		return (1);
	return (0);
}

static void	*check_deading(t_philo *philos)
{
	int		i;
	time_t	tmp;

	tmp = philos[0].glob->die_time;
	while (1)
	{
		i = 0;
		while (i < philos[0].glob->num)
		{
			pthread_mutex_lock(&(philos[i].check_life_mutex));
			if (check_eat_all(philos))
				return (free_all(philos));
			if (get_time(philos[i].glob) - philos[i].eat_t > tmp)
			{
				philo_death(philos + i);
				return (free_all(philos));
			}
			pthread_mutex_unlock(&(philos[i].check_life_mutex));
			i++;
		}
		my_usleep(1000, philos[0].glob);
	}
	return (NULL);
}

int	simulation(t_philo *philos)
{
	int	i;
	int	num;

	i = 0;
	num = philos[0].glob->num;
	if (pthread_create(&philos[0].glob->t,
			NULL, (void *(*)(void *))check_deading, (void *)philos))
		return (-1);
	while (i < num)
	{
		if (pthread_create(&philos[i].ph_thread,
				NULL, (void *(*)(void *))start_thread, (void *)(philos + i)))
			return (-1);
		usleep(10);
		i++;
	}
	if (pthread_join(philos[0].glob->t, NULL))
		return (-1);
	return (0);
}
