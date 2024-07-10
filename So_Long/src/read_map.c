/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:02:40 by hansangmin        #+#    #+#             */
/*   Updated: 2022/10/02 20:53:25 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/read_map.h"
#include <stdio.h>

int	file_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_occur(READ_MAP);
	return (fd);
}

t_list_of_map	*list_add(t_list_of_map	*head, char *buf, int read_byte)
{
	int						idx;
	t_list_of_map			*new_lst;
	static t_list_of_map	*last;

	new_lst = (t_list_of_map *)malloc(sizeof(t_list_of_map));
	if (!new_lst)
		err_occur(READ_MAP);
	new_lst->next = NULL;
	idx = -1;
	while (++idx < read_byte)
		new_lst->part_of_map[idx] = buf[idx];
	new_lst->part_of_map[idx] = 0;
	if (!head)
		head = new_lst;
	else
		last->next = new_lst;
	last = new_lst;
	return (head);
}

t_list_of_map	*make_map_list(int fd, t_list_of_map *head, char **map_array)
{
	int		read_byte;
	int		alloc_size;
	char	buf[10];

	read_byte = 1;
	alloc_size = 0;
	head = NULL;
	while (1)
	{
		read_byte = read(fd, buf, 10);
		if (read_byte <= 0)
			break ;
		head = list_add(head, buf, read_byte);
		alloc_size += read_byte;
	}
	*map_array = (char *)malloc(alloc_size + 1);
	if (!*map_array)
		err_occur(READ_MAP);
	printf("%d\n", alloc_size);
	return (head);
}

void	make_map_array(char *map_array, t_list_of_map *head)
{
	int				idx;
	t_list_of_map	*tmp;

	while (head)
	{
		idx = -1;
		while (head->part_of_map[++idx])
			*map_array++ = head->part_of_map[idx];
		tmp = head;
		head = head->next;
		free(tmp);
	}
	*map_array = '\0';
}

char	*read_map(char *file, char *map_array)
{
	int				fd;
	t_list_of_map	*head;

	head = NULL;
	fd = file_open(file);
	head = make_map_list(fd, head, &map_array);
	close(fd);
	make_map_array(map_array, head);
	return (map_array);
}
