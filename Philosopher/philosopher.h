/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:50:23 by hansangmin        #+#    #+#             */
/*   Updated: 2023/01/12 01:56:53 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_timeval.h>
#include <unistd.h>
#include <sys/time.h>

// 철학자 수 1, 2명일 때 처리
// time_lock 제거

#define TRUE 								(1)
#define FALSE 								(0)

#define NUMBER_OF_PHILOSOPHERS 				(1)
#define TIME_TO_DIE							(2)
#define TIME_TO_EAT							(3)
#define TIME_TO_SLEEP						(4)
#define NUM_OF_TIMES_EACH_PHILOS_MUST_EAT	(5)

struct s_shared;

typedef struct s_philosopher{
	int				id;
	int				number_of_philos;
	int				num_meals;
	int				num_of_times_each_philos_must_eat;
	long		time_to_eat;
	long		time_to_sleep;
	long		time_to_die;
	long 		st_time;
	long 		last_time_eat;
	struct s_shared	*shared;	
}	t_philosopher;

typedef struct s_death_info
{
	int		id;
	long	time;
}	t_death_info;

typedef struct s_shared
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*dead_flag_lock;
	pthread_mutex_t	*wr_lock;
	int				dead_flag;
	int				number_of_eat_up;
	t_death_info	death_info;
	t_philosopher	*philos;
}	t_shared;

/* in tool.c */
long 		renewed_cur_time(long st_time);
void		am_i_dead(t_philosopher *p);
void		ft_msleep(int ms, t_philosopher *p);
long long	ft_atoi(const char *nptr);

/* in routine */
void		*philosopher(void *arg);

/* in init */
int			init(char *av[], t_shared **arg, pthread_t **threads);

#endif
