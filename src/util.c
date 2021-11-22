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
/*
void	ph_sleep(t_philo *philo, int doing_time)
{
	long			t;
	struct timeval	s_start;
	struct timeval	s_end;

	t = *philo->time + doing_time;
	gettimeofday(&s_start, NULL);
	while (*philo->time < t)
	{
		gettimeofday(&s_end, NULL);
		*philo->time = s_end.tv_usec - s_start.tv_usec;
	}
}
*/
long long	get_time(t_philo *philo)
{
	struct timeval	end;
	long long		end_time;
	long long		start_time;

	start_time = philo->start;
	gettimeofday(&end, NULL);
	end_time = end.tv_sec * 1000 + end.tv_usec / 1000;
	end_time -= start_time;
	return (end_time);
}
