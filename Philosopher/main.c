/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:22:24 by hansangmin        #+#    #+#             */
/*   Updated: 2023/01/12 01:56:58 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	ended_check(t_shared *shared)
{
	while (TRUE)
	{
		pthread_mutex_lock(shared->dead_flag_lock);
		if (shared->number_of_eat_up == shared->philos->number_of_philos)
		{
			printf("all philos ate up\n");
			return ;
		}
		if (shared->dead_flag == TRUE)
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
	pthread_t		*threads;
	t_shared		*shared;
	int				idx;

	//올바른 ac인지도 확인해야함
	if (ac != 5 && ac != 6)
		return (1);
	if (init(av, &shared, &threads))
		return (1);
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