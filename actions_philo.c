/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 17:10:28 by lbrandy           #+#    #+#             */
/*   Updated: 2021/07/27 16:18:21 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	think(t_philo *philo)
{
	if (print("is thinking", philo) == -1)
		return (0);
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (print("is sleeping", philo) == -1)
		return (0);
	my_usleep(philo->glob->sleep_time * 1000, philo->glob);
	return (1);
}

int	eat(t_philo *philo)
{
	if (!try_forks(philo))
		return (0);
	if (print("is eating", philo) == -1)
		return (0);
	pthread_mutex_lock(&(philo->check_life_mutex));
	philo->eat_t = get_time(philo->glob);
	pthread_mutex_unlock(&(philo->check_life_mutex));
	if (my_usleep(philo->glob->eat_time * 1000, philo->glob) == -1)
		return (0);
	pthread_mutex_lock(&(philo->check_life_mutex));
	philo->eat_counter++;
	pthread_mutex_unlock(&(philo->check_life_mutex));
	if (!put_forks(philo))
		return (0);
	return (1);
}

int	try_forks(t_philo *philo)
{
	if (!((philo->index - 1) % 2))
	{
		if (pthread_mutex_lock(philo->r_fork))
			return (0);
		print("has taken a fork", philo);
		if (pthread_mutex_lock(philo->l_fork))
			return (0);
		print("has taken a fork", philo);
	}
	else
	{
		if (pthread_mutex_lock(philo->l_fork))
			return (0);
		print("has taken a fork", philo);
		if (pthread_mutex_lock(philo->r_fork))
			return (0);
		print("has taken a fork", philo);
	}
	return (1);
}

int	put_forks(t_philo *philo)
{
	if (!((philo->index - 1) % 2))
	{
		if (pthread_mutex_unlock(philo->l_fork))
			return (0);
		usleep(5);
		if (pthread_mutex_unlock(philo->r_fork))
			return (0);
		usleep(5);
	}
	else
	{
		if (pthread_mutex_unlock(philo->r_fork))
			return (0);
		usleep(5);
		if (pthread_mutex_unlock(philo->l_fork))
			return (0);
		usleep(5);
	}
	return (1);
}
