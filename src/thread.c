/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:41:44 by seongjki          #+#    #+#             */
/*   Updated: 2021/11/22 12:18:15 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%ldms %d has taken a fork\n", *philo->time, philo->name);
	ph_sleep(philo, philo->rule->time_to_eat);
	printf("%ldms %d is eating\n", *philo->time, philo->name);
	pthread_mutex_unlock(philo->print_mutex);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	ph_sleep(philo, philo->rule->time_to_sleep);
	printf("%ldms %d is sleeping\n", *philo->time, philo->name);
	pthread_mutex_unlock(philo->print_mutex);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%ldms %d is thinking\n", *philo->time, philo->name);
	pthread_mutex_unlock(philo->print_mutex);
}

void	*thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(philo->lfork);
	pthread_mutex_lock(philo->rfork);
	eating(philo);
	sleeping(philo);
	thinking(philo);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	return (0);
}
