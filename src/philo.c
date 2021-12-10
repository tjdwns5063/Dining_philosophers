/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:13:55 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/10 13:13:08 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	free_memory(t_info *info)
{
	int	idx;

	idx = 0;
	while (idx < info->num_of_philo)
	{
		if (pthread_mutex_destroy(&info->forks[idx]) != 0)
			return (-1);
		idx++;
	}
	if (pthread_mutex_destroy(&info->print_mutex) != 0)
		return (-1);
	free(info->pthread);
	free(info->forks);
	free(info->philo);
	return (0);
}

int	check_dead_and_end_pthread(t_info *info)
{
	int		idx;

	idx = 0;
	if (info->dead_flag == DEAD)
	{
		while (idx < info->num_of_philo)
		{
			if (info->num_of_philo == 1)
				break ;
			pthread_join(info->pthread[idx], NULL);
			idx++;
		}
		if (free_memory(info) < 0)
			return (-1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_info		info;
	int			idx;

	if (ac < 5 || ac > 6)
		return (-1);
	idx = 1;
	while (idx < ac)
	{
		if (ph_isdigit(av[idx]) < 0)
			return (-1);
		idx++;
	}
	if (init_func(&info, ac, av) < 0)
		return (-1);
	if (make_thread(&info) < 0)
		return (-1);
	if (check_dead_and_end_pthread(&info) < 0)
		return (-1);
	return (0);
}
