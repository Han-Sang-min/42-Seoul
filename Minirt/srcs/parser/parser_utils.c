/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:13:20 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:14:26 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	skip_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			str[i] = ' ';
		i++;
	}
}

int	get_lines(char *file, int id)
{
	int		i;
	int		fd;
	char	*line;
	char	**element;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd <= 0)
		exit_error("Error: File open error\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		skip_whitespace(line);
		element = ft_split(line, ' ');
		if (check_identifier(element[0]) == id)
			i++;
		free_arr(element);
		free(line);
	}
	close(fd);
	return (i);
}

int	count_element(char **element)
{
	int	i;

	i = 0;
	while (element[i])
		i++;
	return (i);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i++] = NULL;
	}
	free(arr);
	arr = NULL;
}

void	free_parser(t_parser *p)
{
	free(p->spheres);
	free(p->planes);
	free(p->cylinders);
}
