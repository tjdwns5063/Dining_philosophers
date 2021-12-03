/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:50:49 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/03 16:20:14 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	even_philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	pthread_mutex_lock(&philo->info->print_mutex);
	if (philo->info->dead_flag != DEAD)
		ph_print(philo, "has taken a l_fork");
	pthread_mutex_unlock(&philo->info->print_mutex);
	pthread_mutex_lock(philo->rfork);
	philo->starve_time = get_time(philo) - philo->eat_time;
	pthread_mutex_lock(&philo->info->print_mutex);
	if (philo->info->dead_flag != DEAD)
		ph_print(philo, "has taken a r_fork");
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	odd_philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	pthread_mutex_lock(&philo->info->print_mutex);
	if (philo->info->dead_flag != DEAD)
		ph_print(philo, "has taken a r_fork");
	pthread_mutex_unlock(&philo->info->print_mutex);
	pthread_mutex_lock(philo->lfork);
	philo->starve_time = get_time(philo) - philo->eat_time;
	pthread_mutex_lock(&philo->info->print_mutex);
	if (philo->info->dead_flag != DEAD)
		ph_print(philo, "has taken a l_fork");
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	if (philo->info->dead_flag != DEAD)
		ph_print(philo, "is eating");
	pthread_mutex_unlock(&philo->info->print_mutex);
	philo->eat_time = get_time(philo);
	philo->starve_time = 0;
	ph_sleep(philo, philo->info->time_to_eat);
	philo->eat_cnt++;
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	if (philo->info->dead_flag != DEAD)
		ph_print(philo, "is thinking");
	pthread_mutex_unlock(&philo->info->print_mutex);
	usleep(200);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	if (philo->info->dead_flag != DEAD)
		ph_print(philo, "is sleeping");
	pthread_mutex_unlock(&philo->info->print_mutex);
	ph_sleep(philo, philo->info->time_to_sleep);
}
