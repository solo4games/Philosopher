/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 12:37:40 by lbrandy           #+#    #+#             */
/*   Updated: 2021/07/27 16:18:03 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*start_thread(t_philo *philo)
{
	pthread_detach(philo->ph_thread);
	while (1)
	{
		if (!eat(philo))
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
		if (!think(philo))
			return (NULL);
	}
	return (NULL);
}

int	start(char **argv, int flag)
{
	t_glob	*glob;
	t_philo	*philo;

	glob = (t_glob *)malloc(sizeof(t_glob));
	if (!glob)
		return (error_message("malloc error\n", -1));
	if (pars_argv(argv, glob, flag) == -1)
		return (error_message("bad argv input\n", -1));
	philo = (t_philo *)malloc(sizeof(t_philo) * glob->num);
	if (!philo)
		return (error_message("malloc error\n", -1));
	if (fill_mass_philo(philo, glob->num, glob) == -1)
		return (error_message("invalid arguments\n", -1));
	if (simulation(philo) == -1)
		return (error_message("something wrong with simulation\n", -1));
	return (0);
}

int	main(int argc, char **argv)
{
	int	flag;

	if (argc < 5 || argc > 6)
		return (error_message("wrong number of arguments\n", -1));
	if (argc == 5)
		flag = 0;
	else
		flag = 1;
	if (start(&(argv[1]), flag) == -1)
		return (-1);
	return (0);
}
