/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:45:04 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/12 01:21:13 by hansangmin       ###   ########.fr       */
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
		*p->shared->dead_flag = TRUE;
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

void	*philosopher(void *arg)
{
	t_philosopher	*p;
	const int		num_of_philos = ((t_philosopher *)arg)->number_of_philos;

	p = (t_philosopher *)arg;
	if (p->number_of_philos == 1)
		while (TRUE)
			am_i_dead(p);
	if (p->id & 1)
		usleep(p->time_to_eat * 100);
	while (TRUE)
	{
		am_i_dead(p);
		pthread_mutex_lock(&p->shared->forks[(p->id + 1) % num_of_philos]);
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
		pthread_mutex_unlock(&p->shared->forks[(p->id + 1) % num_of_philos]);
		pthread_mutex_unlock(&p->shared->forks[p->id]);
		am_i_dead(p);
		p->last_time_eat = renewed_cur_time(p->st_time);
		p->num_meals++;
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
		pthread_mutex_lock(p->shared->wr_lock);
		printf("%ld %d is sleeping\n", renewed_cur_time(p->st_time), p->id);
		pthread_mutex_unlock(p->shared->wr_lock);
		ft_msleep(p->time_to_sleep, p);
		pthread_mutex_lock(p->shared->wr_lock);
		printf("%ld %d is thinking\n", renewed_cur_time(p->st_time), p->id);
		pthread_mutex_unlock(p->shared->wr_lock);
	}
	return (NULL);
}

void	ended_check(t_shared *shared)
{
	while (TRUE)
	{
		pthread_mutex_lock(shared->dead_flag_lock);
		if (shared->number_of_eat_up == shared->philos->number_of_philos)
		{
			printf("all philos ate up\n");
			return ;
		}
		if (*shared->dead_flag == TRUE)
		{
			printf("%ld %d died\n", shared->death_info.time, shared->death_info.id);
			return ;
		}
		pthread_mutex_unlock(shared->dead_flag_lock);
	}
}

int	main(int ac, char *av[])
{
	int				num_of_philos;
	int				num_of_times_each_philos_must_eat;
	pthread_t		*threads;
	t_shared		*shared;
	struct timeval	st_time;
	int				idx;

//올바른 ac인지도 확인해야함
	if (ac != 5 && ac != 6)
		return (1);
	num_of_philos = atoi(av[NUMBER_OF_PHILOSOPHERS]);
	shared = (t_shared *)malloc(sizeof(t_shared));
	shared->forks = malloc(sizeof(pthread_mutex_t) * num_of_philos);
	shared->dead_flag = malloc(sizeof(int));
	shared->dead_flag_lock = malloc(sizeof(pthread_mutex_t));
	shared->wr_lock = malloc(sizeof(pthread_mutex_t));
	shared->philos = (t_philosopher *)malloc(sizeof(t_philosopher) * num_of_philos);
	threads = malloc(sizeof(pthread_t) * (num_of_philos));
	if (!shared->forks || !threads || !shared->philos || !shared->dead_flag_lock || !shared->wr_lock)
		return (1);
	idx = 0;
	*shared->dead_flag = 0;
	shared->number_of_eat_up = 0;
	while (idx < num_of_philos)
		pthread_mutex_init(&shared->forks[idx++], NULL);
	pthread_mutex_init(shared->dead_flag_lock, NULL);
	pthread_mutex_init(shared->wr_lock, NULL);
	idx = -1;
	if (av[NUM_OF_TIMES_EACH_PHILOS_MUST_EAT] == NULL)
		num_of_times_each_philos_must_eat = 0;
	else
		num_of_times_each_philos_must_eat = atoi(av[NUM_OF_TIMES_EACH_PHILOS_MUST_EAT]);
	gettimeofday(&st_time, 0);
	while (++idx < num_of_philos)
	{
		shared->philos[idx] = (t_philosopher) \
		{.id = idx, .num_meals = 0, .st_time = (st_time.tv_sec) * 1000 + st_time.tv_usec / 1000, \
		.last_time_eat = shared->philos[idx].st_time, .number_of_philos = num_of_philos, .shared = shared,\
		.num_of_times_each_philos_must_eat = num_of_times_each_philos_must_eat,\
		.time_to_eat = atoi(av[TIME_TO_EAT]), .time_to_sleep = atoi(av[TIME_TO_SLEEP]), .time_to_die = atoi(av[TIME_TO_DIE])};
	}
	idx = -1;
	while (++idx < num_of_philos)
		pthread_create(&threads[idx], NULL, philosopher, (void *)(shared->philos + idx));
	ended_check(shared);
	idx = -1;
	while (++idx < num_of_philos)
		pthread_detach(threads[idx]);
	idx = 0;
	while (idx < num_of_philos)
		pthread_mutex_destroy(&shared->forks[idx++]);
	pthread_mutex_destroy(shared->dead_flag_lock);
}