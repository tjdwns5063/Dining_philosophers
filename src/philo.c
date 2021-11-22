/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:13:55 by seongjki          #+#    #+#             */
/*   Updated: 2021/11/22 18:13:27 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rule	init_rule(int ac, char **av)
{
	t_rule	ret;

	ret.num_of_philo = ft_atoi(av[1]);
	ret.time_to_die = ft_atoi(av[2]);
	ret.time_to_eat = ft_atoi(av[3]);
	ret.time_to_sleep = ft_atoi(av[4]);
	if (ac > 5)
		ret.must_eat = ft_atoi(av[5]);
	else
		ret.must_eat = -1;
	return (ret);
}

void	init_philo(t_philo_info *philo_info)
{
	int				idx;
	struct timeval	start;

	idx = 0;
	gettimeofday(&start, NULL);
	while (idx < philo_info->rule.num_of_philo)
	{
		philo_info->philo[idx].name = idx + 1;
		philo_info->philo[idx].rfork = &philo_info->forks[idx];
		philo_info->philo[idx].rule = &philo_info->rule;
		philo_info->philo[idx].start = start.tv_sec * 1000 + start.tv_usec / 1000;
		philo_info->philo[idx].print_mutex = &philo_info->print_mutex;
		philo_info->philo[idx].starve_time = 0;
		if (idx == philo_info->rule.num_of_philo - 1)
			philo_info->philo[idx].lfork = &philo_info->forks[0];
		else
			philo_info->philo[idx].lfork = &philo_info->forks[idx + 1];
		idx++;
	}
}

t_philo_info	init_philo_info(int ac, char **av)
{
	t_philo_info	ret;
	int				size;
	int				idx;

	size = ft_atoi(av[1]);
	ret.philo = (t_philo *)malloc(sizeof(t_philo) * (size));
	ret.p_threads = (pthread_t *)malloc(sizeof(pthread_t) * (size));
	ret.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (size));
	idx = 0;
	while (idx < size)
	{
		pthread_mutex_init(&ret.forks[idx], NULL);
		idx++;
	}
	pthread_mutex_init(&ret.print_mutex, NULL);
	ret.rule = init_rule(ac, av);
	return (ret);
}

int	main(int ac, char **av)
{
	t_philo_info	philo_info;
	int				size;
	int				idx;

	if (ac <= 4)
		exit(0);
	size = ft_atoi(av[1]);
	philo_info = init_philo_info(ac, av);
	init_philo(&philo_info);
	idx = 0;
	while (idx < size)
	{
		pthread_create(&philo_info.p_threads[idx], NULL, thread, (void *)&philo_info.philo[idx]);
		idx++;
	}
	idx = 0;
	while (idx < size)
	{
		if (pthread_join(philo_info.p_threads[idx], NULL) == 0)
			idx++;
	}
}
