/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:14:02 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/09 19:15:42 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define ALIVE	1
# define DEAD	0

typedef struct s_philo
{
	int				name;
	int				state;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	long long		eat_cnt;
	long long		eat_time;
	long long		starve_time;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long			start_time;
	int				dead_flag;
	pthread_t		*pthread;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}	t_info;

/* init.c */
int			init_func(t_info *info, int ac, char **av);
/* thread.c */
int			make_thread(t_info *info);
/* routine.c */
void		even_philo_take_fork(t_philo *philo);
void		odd_philo_take_fork(t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
/* utils.c */
int			ft_atoi(const char *str);
void		ph_sleep(t_philo *philo, int doing_time);
long long	get_time(t_philo *philo);
void		ph_print(t_philo *philo, char *print_str);
int			ph_isdigit(char *str);

#endif
