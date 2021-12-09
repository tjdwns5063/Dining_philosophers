/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:18:51 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/09 18:28:54 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo(t_info *info)
{
	int				idx;

	idx = 0;
	while (idx < info->num_of_philo)
	{
		info->philo[idx].name = idx + 1;
		info->philo[idx].eat_cnt = 0;
		info->philo[idx].rfork = &(info->forks[idx]);
		info->philo[idx].starve_time = 0;
		info->philo[idx].eat_time = 0;
		if (idx == info->num_of_philo - 1)
			info->philo[idx].lfork = &(info->forks[0]);
		else
			info->philo[idx].lfork = &(info->forks[idx + 1]);
		info->philo[idx].info = info;
		idx++;
	}
	return (1);
}

static int	init_malloc(t_info *info)
{
	int	idx;

	info->philo = (t_philo *)malloc(sizeof(t_philo) * (info->num_of_philo));
	if (info->philo == NULL)
		return (0);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
	 (info->num_of_philo));
	if (info->forks == NULL)
	{
		free(info->philo);
		return (0);
	}
	idx = 0;
	while (idx < info->num_of_philo)
	{
		if (pthread_mutex_init(&info->forks[idx], NULL) != 0)
			return (0);
		idx++;
	}
	if (pthread_mutex_init(&info->print_mutex, NULL) != 0)
		return (0);
	return (1);
}

static int	init_info(t_info *info, int ac, char **av)
{
	struct timeval	start;

	info->num_of_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac != 6)
		info->must_eat = -1;
	else
		info->must_eat = ft_atoi(av[5]);
	info->dead_flag = ALIVE;
	gettimeofday(&start, NULL);
	info->pthread = (pthread_t *)malloc(sizeof(pthread_t) * (info->num_of_philo));
	if (!info->pthread)
		return (0);
	info->start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
	return (1);
}

int	init_func(t_info *info, int ac, char **av)
{
	if (!init_info(info, ac, av))
		return (0);
	if (!init_malloc(info))
		return (0);
	if (!init_philo(info))
		return (0);
	return (1);
}
