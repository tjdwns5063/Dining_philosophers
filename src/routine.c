/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:50:49 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/07 14:51:05 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	even_philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	ph_print(philo, "has taken a l_fork");
	pthread_mutex_lock(philo->rfork);
	philo->starve_time = get_time(philo) - philo->eat_time;
	ph_print(philo, "has taken a r_fork");
}

void	odd_philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	ph_print(philo, "has taken a r_fork");
	pthread_mutex_lock(philo->lfork);
	philo->starve_time = get_time(philo) - philo->eat_time;
	ph_print(philo, "has taken a l_fork");
}

void	eating(t_philo *philo)
{
	ph_print(philo, "is eating");
	philo->eat_time = get_time(philo);
	philo->starve_time = 0;
	ph_sleep(philo, philo->info->time_to_eat);
	philo->eat_cnt++;
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

void	thinking(t_philo *philo)
{
	ph_print(philo, "is thinking");
	usleep(200);
}

void	sleeping(t_philo *philo)
{
	ph_print(philo, "is sleeping");
	ph_sleep(philo, philo->info->time_to_sleep);
}
