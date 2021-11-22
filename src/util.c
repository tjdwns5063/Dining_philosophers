#include "philo.h"

static int	cnt_len(long long n)
{
	int			cnt;

	cnt = 0;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		cnt += 1;
	}
	return (cnt);
}

static void	make_str(char *str, int n, int cnt)
{
	long long	nbr;

	nbr = n;
	if (nbr < 0)
		nbr *= -1;
	while (nbr)
	{
		*(str + cnt - 1) = nbr % 10 + '0';
		nbr /= 10;
		cnt--;
	}
}

char	*ft_itoa(int n)
{
	int			cnt;
	char		*ret;

	cnt = cnt_len(n) + (n <= 0);
	ret = (char *)malloc(sizeof(char) * (cnt + 1));
	if (!ret)
		return (0);
	ret[cnt] = '\0';
	if (n < 0)
		*ret = '-';
	if (n == 0)
		*ret = '0';
	make_str(ret, n, cnt);
	return (ret);
}

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
	long			t;
	struct timeval	start;
	struct timeval	end;

	t = *philo->time + doing_time;
	gettimeofday(&start, NULL);
	while (*philo->time < t)
	{
		gettimeofday(&end, NULL);
		*philo->time += end.tv_usec - start.tv_usec;
	}
}
