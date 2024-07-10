/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:15:53 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:15:54 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/include/ft_printf.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include "minirt.h"
# include "structures.h"

void		parse_sphere(t_parser *scene, char **element);
void		parse_plane(t_parser *scene, char **element);
void		parse_cylinder(t_parser *scene, char **element);

double		parse_double(char *str);
double		parse_double_range(char *str, double from, double to);
t_vec3		parse_coordinate(char *str);
t_vec3		parse_coordinate_range(char *str, double from, double to, int norm);

void		parse_ambient(t_parser *scene, char **element);
void		parse_camera(t_parser *scene, char **element);
void		parse_light(t_parser *scene, char **element);

void		parse_line(t_parser *scene, char *line);
void		parse(t_parser *scene, char *file);
void		parser_init(t_parser *scene, char *file);

void		skip_whitespace(char *str);
int			get_lines(char *file, int id);
int			count_element(char **element);
void		free_arr(char **arr);
void		free_parser(t_parser *p);

int			check_identifier(char *id);
void		check_extension(char *file);
char		*check_number(char *num);

#endif
