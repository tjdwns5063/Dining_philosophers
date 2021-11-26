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
	if (ret >= LONG_MAX && sign == 1)
		return ((int)LONG_MAX);
	if (ret >= ((unsigned long)LONG_MIN) && sign == -1)
		return ((int)LONG_MIN);
	return (ret * sign);
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

void	ph_print(t_philo *philo, char *print_str, int state)
{
	if (state == 0 && philo->info->dead_flag != DEAD)
		printf("%lldms %d is %s [%d] [%lld]\n", get_time(philo), philo->name, print_str, philo->eat_cnt, philo->starve_time);
	else if (state == 1 && philo->info->dead_flag != DEAD)
		printf("%lldms %d has taken a %s [%d] [%lld]\n", get_time(philo), philo->name, print_str, philo->eat_cnt, philo->starve_time);
}
