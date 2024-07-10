/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:25:56 by hansangmin        #+#    #+#             */
/*   Updated: 2023/01/12 01:39:46 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	eat(t_philosopher *p)
{
	am_i_dead(p);
	pthread_mutex_lock(&p->shared->forks[(p->id + 1) % p->number_of_philos]);
	pthread_mutex_lock(p->shared->wr_lock);
	printf("%ld %d has taken a fork\n", renewed_cur_time(p->st_time), p->id);
	pthread_mutex_unlock(p->shared->wr_lock);
	pthread_mutex_lock(&p->shared->forks[p->id]);
	am_i_dead(p);
	pthread_mutex_lock(p->shared->wr_lock);
	printf("%ld %d has taken a fork\n", renewed_cur_time(p->st_time), p->id);
	printf("%ld %d is eating\n", renewed_cur_time(p->st_time), p->id);
	pthread_mutex_unlock(p->shared->wr_lock);
	ft_msleep(p->time_to_eat, p);
	pthread_mutex_unlock(&p->shared->forks[(p->id + 1) % p->number_of_philos]);
	pthread_mutex_unlock(&p->shared->forks[p->id]);
	am_i_dead(p);
	p->last_time_eat = renewed_cur_time(p->st_time);
	p->num_meals++;
}

static void	sleep_think(t_philosopher *p)
{
	pthread_mutex_lock(p->shared->wr_lock);
	printf("%ld %d is sleeping\n", renewed_cur_time(p->st_time), p->id);
	pthread_mutex_unlock(p->shared->wr_lock);
	ft_msleep(p->time_to_sleep, p);
	pthread_mutex_lock(p->shared->wr_lock);
	printf("%ld %d is thinking\n", renewed_cur_time(p->st_time), p->id);
	pthread_mutex_unlock(p->shared->wr_lock);
}

void	*philosopher(void *arg)
{
	t_philosopher	*p;

	p = (t_philosopher *)arg;
	if (p->number_of_philos == 1)
		while (TRUE)
			am_i_dead(p);
	if (p->id & 1)
		usleep(p->time_to_eat * 100);
	while (TRUE)
	{
		eat(p);
		if (p->num_of_times_each_philos_must_eat != 0)
		{
			if (p->num_meals >= p->num_of_times_each_philos_must_eat)
			{
				pthread_mutex_lock(p->shared->dead_flag_lock);
				p->shared->number_of_eat_up++;
				pthread_mutex_unlock(p->shared->dead_flag_lock);
				break ;
			}
		}
		sleep_think(p);
	}
	return (NULL);
}
