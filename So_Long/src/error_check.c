/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:55:43 by hansangmin        #+#    #+#             */
/*   Updated: 2022/10/02 20:52:58 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_every_element(char cell_of_map, \
int *check_element, t_data_of_board *t_dob)
{
	int	mark;

	mark = 0;
	if (cell_of_map == '1')
		mark = WALL;
	else if (cell_of_map == 'C')
	{
		t_dob->feed_size++;
		mark = FEED;
	}
	else if (cell_of_map == 'E')
		mark = EXIT;
	else if (cell_of_map == 'P')
		mark = PLAYER;
	if (*check_element & mark)
		return (mark);
	return (0);
}

void	square_check(int *number_of_row, int idx)
{
	printf("%d : %d\n", *number_of_row, idx);
	if (idx == 0)
		err_occur_msg("A map cannot start with newline");
	if (!*number_of_row)
		*number_of_row = idx;
	else if (idx % *number_of_row != 0)
		err_occur_msg("It's not a square");
}

void	check_the_wall(const int number_of_columns, \
const char *map_array, const int idx)
{
	int	i;

	i = -1;
	if (number_of_columns == 1)
		while (map_array[++i] != '\n')
			if (map_array[i] != '1')
				err_occur_msg("Wall check error");
	if (map_array[idx - 1] != '1' || \
	map_array[idx] == '\0' || map_array[idx + 1] != '1')
	{
		if (map_array[idx] == '\0')
		{
			i = 0;
			while (map_array[idx - ++i] != '\n')
				if (map_array[idx - i] != '1')
					err_occur_msg("Wall check error");
			return ;
		}
		err_occur_msg("Wall check error");
	}
}

void	error_check(int argc, t_data_of_board *t_dob)
{
	int	check_element;
	int	idx;

	if (argc != 2)
		err_occur_msg("Number of argument error");
	check_element = INIT_ELEMENT_CHECK;
	idx = -1;
	while (t_dob->map[++idx])
	{
		check_element -= \
		check_every_element(t_dob->map[idx], &check_element, t_dob);
		if (t_dob->map[idx] == '\n' || t_dob->map[idx + 1] == '\0')
		{
			if (t_dob->map[idx] == '\n' && t_dob->map[idx + 1] == '\0')
				err_occur_msg("Map error(new line error)");
			if (t_dob->map[idx + 1] == '\0')
				idx++;
			square_check(&t_dob->row, idx - t_dob->columns++);
			check_the_wall(t_dob->columns, t_dob->map, idx);
			if (t_dob->map[idx] == '\0')
				idx--;
		}
	}
	if (check_element)
		err_occur_msg("Lack of element");
}
