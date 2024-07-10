/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:14:22 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:14:23 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_sphere(t_parser *scene, char **element)
{
	static int	i;

	if (count_element(element) != 4)
		exit_error("Error: invalid args in sp\n");
	scene->spheres[i].center = parse_coordinate(element[1]);
	scene->spheres[i].diameter = parse_double(element[2]);
	if (scene->spheres[i].diameter < 0)
		exit_error("Error: sp diameter is negative\n");
	scene->spheres[i].rgb = \
	parse_coordinate_range(element[3], 0.0, 255.0, 0);
	i++;
}

void	parse_plane(t_parser *scene, char **element)
{
	static int	i;

	if (count_element(element) != 4)
		exit_error("Error: invalid args in pl\n");
	scene->planes[i].coord = parse_coordinate(element[1]);
	scene->planes[i].orientation = \
	parse_coordinate_range(element[2], -1.0, 1.0, 1);
	scene->planes[i].rgb = \
	parse_coordinate_range(element[3], 0.0, 255.0, 0);
	i++;
}

void	parse_cylinder(t_parser *scene, char **element)
{
	static int	i;

	if (count_element(element) != 6)
		exit_error("Error: invalid args in cy\n");
	scene->cylinders[i].coord = parse_coordinate(element[1]);
	scene->cylinders[i].orientation = \
	parse_coordinate_range(element[2], -1.0, 1.0, 1);
	scene->cylinders[i].diameter = parse_double(element[3]);
	scene->cylinders[i].height = parse_double(element[4]);
	scene->cylinders[i].rgb = \
	parse_coordinate_range(element[5], 0.0, 255.0, 0);
	if (scene->cylinders[i].diameter < 0 ||  \
	scene->cylinders[i].height < 0)
		exit_error("Error: cy args is negative\n");
	i++;
}
