/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_points.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:14:21 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:14:22 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

double	parse_double(char *str)
{
	char	**splitted;
	double	res;
	int		is_double;

	splitted = ft_split(str, '.');
	is_double = count_element(splitted);
	res = 0;
	if (is_double == 1)
		res = (double)(ft_atoi(check_number(splitted[0])));
	else if (is_double == 2)
	{
		res = (double)(ft_atoi(check_number(splitted[1])));
		if (res < 0)
			exit_error("minus sign in decimal?\n");
		res /= pow(10, ft_strlen(splitted[1]));
		if (splitted[0][0] == '-' && res > 0)
			res *= -1;	
		res += (double)ft_atoi(check_number(splitted[0]));
	}
	else
		exit_error("Error: parse error\n");
	free_arr(splitted);
	return (res);
}

double	parse_double_range(char *str, double from, double to)
{
	double	res;

	res = parse_double(str);
	if (res < from || res > to)
		exit_error("Error: out of range\n");
	return (res);
}

t_vec3	parse_coordinate(char *str)
{
	char	**splitted;
	t_vec3	coordinate;

	splitted = ft_split(str, ',');
	if (count_element(splitted) != 3)
		exit_error("Error: coordinates\n");
	coordinate.x = parse_double(splitted[0]);
	coordinate.y = parse_double(splitted[1]);
	coordinate.z = parse_double(splitted[2]);
	free_arr(splitted);
	return (coordinate);
}

t_vec3	parse_coordinate_range(char *str, double from, double to, int norm)
{
	t_vec3	v;

	v = parse_coordinate(str);
	if (v.x < from || v.x > to || \
	v.y < from || v.y > to || v.z < from || v.z > to)
		exit_error("coordinate out of defined range\n");
	if (norm)
		return (vunit(v));
	return (v);
}
