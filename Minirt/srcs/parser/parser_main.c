/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:14:23 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:14:24 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "parser.h"

void	parse_line(t_parser *scene, char *line)
{
	char	**element;
	int		id;

	element = ft_split(line, ' ');
	id = check_identifier(element[0]);
	if (id == 0)
		;
	else if (id == 1)
		parse_ambient(scene, element);
	else if (id == 2)
		parse_camera(scene, element);
	else if (id == 3)
		parse_light(scene, element);
	else if (id == 4)
		parse_sphere(scene, element);
	else if (id == 5)
		parse_plane(scene, element);
	else if (id == 6)
		parse_cylinder(scene, element);
	else
		exit_error("Error: invalid identifier\n");
	free_arr(element);
}

void	parse(t_parser *scene, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd <= 0)
		exit_error("Error: Cannot open file\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		skip_whitespace(line);
		parse_line(scene, line);
		free(line);
	}
	close(fd);
}

void	parser_init(t_parser *scene, char *file)
{
	check_extension(file);
	if (!get_lines(file, 1) || !get_lines(file, 2) || !get_lines(file, 3))
		exit_error("Error: No lighting or camera identifier\n");
	scene->s = get_lines(file, 4);
	scene->p = get_lines(file, 5);
	scene->cy = get_lines(file, 6);
	scene->light.light_point = vec3(0, 0, 0);
	scene->light.ratio = 1;
	scene->light.rgb = color3(0, 0, 0);
	scene->spheres = \
	(t_parser_sp *)malloc(sizeof(t_parser_sp) * scene->s);
	scene->planes = \
	(t_parser_pl *)malloc(sizeof(t_parser_pl) * scene->p);
	scene->cylinders = \
	(t_parser_cy *)malloc(sizeof(t_parser_cy) * scene->cy);
	parse(scene, file);
}
