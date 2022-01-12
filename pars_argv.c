/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 13:26:26 by lbrandy           #+#    #+#             */
/*   Updated: 2021/07/27 15:17:51 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	len_argv(char **argv)
{
	int	len;

	len = 0;
	while (argv[len])
		len++;
	return (len);
}

static int	check_symbol(char c)
{
	return (c == ' '
		|| c == '\n'
		|| c == '\t'
		|| c == '\r'
		|| c == '\v'
		|| c == '\f'
		|| c == '+');
}

static int	check_number(char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (check_symbol(str[i]))
		i++;
	if (str[i] == '-' || !(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	if (ft_strlen(&str[i]) > 10)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (num > INT_MAX)
		return (-1);
	return (num);
}

static int	choice(int tmp, t_glob *glob, int flag, int i)
{
	if (tmp == -1)
		return (-1);
	if ((i == 0 || (i == 4 && flag == 1)) && tmp == 0)
		return (-1);
	if (i == 0)
		glob->num = tmp;
	if (i == 1)
		glob->die_time = (time_t)tmp;
	if (i == 2)
		glob->eat_time = (time_t)tmp;
	if (i == 3)
		glob->sleep_time = (time_t)tmp;
	if (flag == 1 && i == 4)
		glob->eat_num = tmp;
	return (0);
}

int	pars_argv(char **argv, t_glob *glob, int flag)
{
	int	i;
	int	tmp;
	int	len;

	i = 0;
	len = len_argv(argv);
	glob->eat_num = -1;
	while (i < len)
	{
		tmp = check_number(argv[i]);
		if (choice(tmp, glob, flag, i) == -1)
			return (-1);
		i++;
	}
	if (glob->num < 1 || glob->die_time < 1
		|| glob->eat_time < 1 || glob->sleep_time < 1)
		return (-1);
	if (gettimeofday(&glob->start_t, NULL) == -1)
		return (-1);
	glob->print = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(glob->print, NULL))
		return (-1);
	return (0);
}
