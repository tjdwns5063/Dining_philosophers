/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:41:23 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/03 16:41:14 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned long	ret;
	long			sign;

	ret = 0;
	sign = 1;
	while (*str && ((9 <= *str && *str <= 13) || *str == ' '))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ('0' <= *str && *str <= '9'))
	{
		ret *= 10;
		ret += *str - '0';
		str++;
	}
	return (ret * sign);
}

int	ph_isdigit(char *str)
{
	int	idx;

	if (!str)
		return (0);
	idx = 0;
	while (str[idx])
	{
		if (str[idx] < '0' || str[idx] > '9')
		{
			printf("Argument is Always Positive Integer!!\n");
			return (0);
		}
		idx++;
	}
	return (1);
}

void	ph_sleep(t_philo *philo, int doing_time)
{
	long long	current;
	long long	next;

	current = get_time(philo);
	next = current + doing_time;
	while (current < next)
	{
		current = get_time(philo);
		usleep(100);
	}
}

long long	get_time(t_philo *philo)
{
	struct timeval	end;
	long long		end_time;

	gettimeofday(&end, NULL);
	end_time = end.tv_sec * 1000 + end.tv_usec / 1000;
	return (end_time - philo->info->start_time);
}

void	ph_print(t_philo *philo, char *print_str)
{
	if (philo->info->dead_flag != DEAD)
	{
		printf("%lldms %d %s [%d] [%lld]\n", get_time(philo), \
philo->name, print_str, philo->eat_cnt, philo->starve_time);
	}
}
