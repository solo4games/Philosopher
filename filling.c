/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:52:37 by lbrandy           #+#    #+#             */
/*   Updated: 2021/07/27 15:32:17 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	fill_mass_forks(pthread_mutex_t *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (-1);
		i++;
	}
	return (0);
}

static pthread_mutex_t	*init_forks(int num)
{
	pthread_mutex_t	*forks;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (!forks)
		return (NULL);
	if (fill_mass_forks(forks, num) == -1)
		return (NULL);
	return (forks);
}

int	fill_mass_philo(t_philo *philos, int num, t_glob *glob)
{
	int				i;
	int				fork_index;
	pthread_mutex_t	*forks;

	forks = init_forks(num);
	if (!forks)
		return (-1);
	i = 0;
	while (i < num)
	{
		if (i - 1 < 0)
			fork_index = num - 1;
		else
			fork_index = i - 1;
		philos[i].index = i + 1;
		philos[i].l_fork = &(forks[fork_index]);
		philos[i].r_fork = &(forks[i]);
		if (pthread_mutex_init(&(philos[i].check_life_mutex), NULL))
			return (-1);
		philos[i].eat_counter = 0;
		philos[i].glob = glob;
		philos[i].eat_t = get_time(glob);
		i++;
	}
	return (0);
}
