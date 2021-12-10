/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:41:44 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/10 13:31:14 by seongjki         ###   ########.fr       */
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

	if (info->philo[idx].eat_cnt >= info->must_eat)
		cnt++;
	if (cnt == info->num_of_philo)
	{
		pthread_mutex_lock(&info->print_mutex);
		printf("All philos were eat at least %d times!!!\n", info->must_eat);
		pthread_mutex_unlock(&info->print_mutex);
		info->dead_flag = DEAD;
	}
	if (idx == info->num_of_philo - 1)
		cnt = 0;
	return ;
}

void	*monitor_thread(t_info *data)
{
	int		idx;
	t_info	*info;

	info = (t_info *)data;
	idx = 0;
	while (info->dead_flag != DEAD)
	{
		check_philo_is_dead(info, idx);
		if (info->must_eat > 0 && info->dead_flag == ALIVE)
			philo_is_all_eat(info, idx);
		idx++;
		if (idx > info->num_of_philo - 1)
			idx = 0;
		usleep(50);
	}
	return (0);
}

void	*philo_thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->name % 2 == 0)
		usleep(50);
	while (philo->info->dead_flag != 0)
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
	int			idx;

	idx = 0;
	while (idx < info->num_of_philo)
	{	
		if (pthread_create(&info->pthread[idx], NULL, philo_thread, \
		(void *)&info->philo[idx]) != 0)
			return (-1);
		if (info->num_of_philo == 1)
		{
			if (pthread_detach(info->pthread[idx]) != 0)
				return (-1);
		}
		idx++;
	}
	monitor_thread(info);
	return (0);
}
