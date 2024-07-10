/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:24:27 by hansangmin        #+#    #+#             */
/*   Updated: 2023/01/12 02:03:40 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init(char *av[], t_shared **shared, pthread_t **threads)
{
	int				num_of_philos;
	int				num_of_times_each_philos_must_eat;
	struct timeval	st_time;
	int				idx;

	num_of_philos = ft_atoi(av[NUMBER_OF_PHILOSOPHERS]);
	(*shared) = (t_shared *)malloc(sizeof(t_shared));
	(*shared)->forks = malloc(sizeof(pthread_mutex_t) * num_of_philos);
	(*shared)->dead_flag_lock = malloc(sizeof(pthread_mutex_t));
	(*shared)->wr_lock = malloc(sizeof(pthread_mutex_t));
	(*shared)->philos = (t_philosopher *)malloc(sizeof(t_philosopher) * num_of_philos);
	*threads = malloc(sizeof(pthread_t) * (num_of_philos));
	if (!*shared || !(*shared)->forks || !*threads || !(*shared)->philos || !(*shared)->dead_flag_lock || !(*shared)->wr_lock)
		return (1);
	idx = 0;
	(*shared)->dead_flag = FALSE;
	(*shared)->number_of_eat_up = 0;
	while (idx < num_of_philos)
		pthread_mutex_init(&(*shared)->forks[idx++], NULL);
	pthread_mutex_init((*shared)->dead_flag_lock, NULL);
	pthread_mutex_init((*shared)->wr_lock, NULL);
	idx = -1;
	if (av[NUM_OF_TIMES_EACH_PHILOS_MUST_EAT] == NULL)
		num_of_times_each_philos_must_eat = 0;
	else
		num_of_times_each_philos_must_eat = ft_atoi(av[NUM_OF_TIMES_EACH_PHILOS_MUST_EAT]);
	gettimeofday(&st_time, 0);
	while (++idx < num_of_philos)
	{
		(*shared)->philos[idx] = (t_philosopher) \
		{.id = idx, .num_meals = 0, .st_time = (st_time.tv_sec) * 1000 + st_time.tv_usec / 1000, \
		.last_time_eat = (*shared)->philos[idx].st_time, .number_of_philos = num_of_philos, .shared = *shared,\
		.num_of_times_each_philos_must_eat = num_of_times_each_philos_must_eat,\
		.time_to_eat = ft_atoi(av[TIME_TO_EAT]), .time_to_sleep = ft_atoi(av[TIME_TO_SLEEP]), .time_to_die = ft_atoi(av[TIME_TO_DIE])};
	}
	return (0);
}