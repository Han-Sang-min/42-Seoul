/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:13:07 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:13:49 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_ambient(t_parser *scene, char **element)
{
	static int	flg;

	if (flg)
		exit_error("Error: Multiple definitions of identifier: A\n");
	flg = 1;
	if (count_element(element) != 3)
		exit_error("Error: Invalid args in identifier: A\n");
	scene->ambient_light.ratio = \
	parse_double_range(element[1], 0.0, 1.0);
	scene->ambient_light.rgb = \
	parse_coordinate_range(element[2], 0.0, 255.0, 0);
}

void	parse_camera(t_parser *scene, char **element)
{
	static int	flg;

	if (flg)
		exit_error("Error: Multiple definitions of identifier: C\n");
	flg = 1;
	if (count_element(element) != 4)
		exit_error("Error: Invalid args in identifier: C\n");
	scene->camera.view_point = parse_coordinate(element[1]);
	scene->camera.orientation = \
	parse_coordinate_range(element[2], -1.0, 1.0, 1);
	scene->camera.fov = parse_double_range(element[3], 0.0, 180.0);
}

void	parse_light(t_parser *scene, char **element)
{
	static int	flg;

	if (flg)
		exit_error("Error: Multiple definitions of identifier: L\n");
	flg = 1;
	if (count_element(element) != 4)
		exit_error("Error: Invalid args in identifier:\n");
	scene->light.light_point = parse_coordinate(element[1]);
	scene->light.ratio = parse_double_range(element[2], 0.0, 1.0);
	scene->light.rgb = parse_coordinate_range(element[3], 0.0, 255.0, 0);
}
