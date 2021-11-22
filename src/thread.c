/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:41:44 by seongjki          #+#    #+#             */
/*   Updated: 2021/11/22 18:13:26 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
void	sleeping(t_philo *philo)
{
	//ph_sleep(philo, philo->rule->time_to_sleep);
	pthread_mutex_lock(philo->print_mutex);
	printf("%ldms %d is sleeping\n", *philo->time, philo->name);
	pthread_mutex_unlock(philo->print_mutex);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%ldms %d is thinking\n", *philo->time, philo->name);
	pthread_mutex_unlock(philo->print_mutex);
}
*/
void	eating(t_philo *philo)
{
	long long	time;

	time = get_time(philo);
	pthread_mutex_lock(philo->print_mutex);
	printf("%lldms %d has taken a fork\n", time, philo->name);
	printf("%lldms %d is eating\n", time, philo->name);
	pthread_mutex_unlock(philo->print_mutex);
	usleep(philo->rule->time_to_eat * 1000);
	time = get_time(philo);
	philo->start += time;
	//ph_sleep(philo, philo->rule->time_to_eat);
}


void	*thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

	pthread_mutex_lock(philo->lfork);
	pthread_mutex_lock(philo->rfork);
	eating(philo);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	//sleeping(philo);
	//thinking(philo);
	return (0);
}
