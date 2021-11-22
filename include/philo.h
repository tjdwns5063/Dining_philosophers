/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:14:02 by seongjki          #+#    #+#             */
/*   Updated: 2021/11/22 16:55:22 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_rule
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
}	t_rule;

typedef struct s_philo
{
	int				name;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	long long		start;
	long long		starve_time;
	pthread_mutex_t *print_mutex;
	t_rule			*rule;
}	t_philo;

typedef struct s_philo_info
{
	t_philo			*philo;
	pthread_mutex_t *forks;
	pthread_t		*p_threads;
	pthread_mutex_t print_mutex;
	t_rule			rule;
}	t_philo_info;

char		*ft_itoa(int n);
int			ft_atoi(const char *str);
void		*thread(void *data);
void		ph_sleep(t_philo *philo, int doing_time);
long long	get_time(t_philo *philo);

#endif
