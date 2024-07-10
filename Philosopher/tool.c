/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:23:43 by hansangmin        #+#    #+#             */
/*   Updated: 2023/01/12 01:52:30 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long renewed_cur_time(long st_time)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, 0);
	return ((cur_time.tv_sec) * 1000 + (cur_time.tv_usec) / 1000 - st_time);
}

void	am_i_dead(t_philosopher *p)
{	
	const long cur_time = renewed_cur_time(p->st_time);

	if (cur_time - p->last_time_eat > p->time_to_die)
	{
		pthread_mutex_lock(p->shared->wr_lock);
		pthread_mutex_lock(p->shared->dead_flag_lock);
		p->shared->dead_flag = TRUE;
		p->shared->death_info.id = p->id;
		p->shared->death_info.time = cur_time;
		pthread_mutex_unlock(p->shared->dead_flag_lock);
	}
}

void	ft_msleep(int ms, t_philosopher *p)
{
	struct timeval	cur_time;
	long			target_time;

	gettimeofday(&cur_time, 0);
	target_time = ((cur_time.tv_sec) * 1000 + (cur_time.tv_usec) / 1000) + ms;
	while (target_time > (cur_time.tv_sec) * 1000 + (cur_time.tv_usec) / 1000)
	{
		am_i_dead(p);
		usleep(1000);
		gettimeofday(&cur_time, 0);
	}
}

long long	ft_atoi(const char *nptr)
{
	int			sign;
	long long	res;
	size_t		tmp;

	sign = 1;
	res = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign = -1;
	while (*nptr >= 48 && *nptr <= 57)
	{
		tmp = res * 10 + *nptr++ - 48;
		if (tmp > 9223372036854775807U && sign == 1)
			return (-1);
		if ((tmp > 9223372036854775808U && sign == -1))
			return (0);
		res = tmp;
	}
	return (sign * res);
}
