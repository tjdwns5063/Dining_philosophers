/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:41:44 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/03 16:44:30 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_philo_is_dead(t_info *info, int idx)
{
	info->philo[idx].starve_time = \
	get_time(&info->philo[idx]) - info->philo[idx].eat_time;
	if (info->philo[idx].starve_time > info->time_to_die)
	{
		ph_print(&info->philo[idx], "is died");
		info->dead_flag = DEAD;
	}
}

static void	philo_is_all_eat(t_info *info, int idx)
{
	static int	cnt;

	if (info->must_eat < 0)
		return ;
	if (info->philo[idx].eat_cnt == info->must_eat)
	{
		cnt++;
		if (cnt == info->num_of_philo)
		{
			ph_print(&info->philo[idx], "all philo is eating");
			info->dead_flag = DEAD;
		}
	}
	if (idx == info->num_of_philo - 1)
		cnt = 0;
	return ;
}

void	*monitor_thread(void *data)
{
	t_info	*info;
	int		idx;

	info = (t_info *)data;
	idx = 0;
	while (1)
	{
		if (idx > info->num_of_philo - 1)
			idx = 0;
		check_philo_is_dead(info, idx);
		philo_is_all_eat(info, idx);
		idx++;
		usleep(150);
	}
	return (0);
}

void	*philo_thread(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->name % 2 == 0)
		usleep(100);
	while (1)
	{
		if (philo->name % 2 == 0)
			even_philo_take_fork(philo);
		else
			odd_philo_take_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (0);
}

int	make_thread(t_info *info)
{
	pthread_t	pthread;
	pthread_t	monitor;
	int			idx;

	idx = 0;
	while (idx < info->num_of_philo)
	{
		pthread_create(&pthread, NULL, philo_thread, (void *)&info->philo[idx]);
		pthread_detach(pthread);
		idx++;
	}
	pthread_create(&monitor, NULL, monitor_thread, (void *)info);
	pthread_detach(monitor);
	return (0);
}
