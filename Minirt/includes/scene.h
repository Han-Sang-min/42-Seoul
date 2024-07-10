/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:15:54 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:15:55 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"
# include "minirt.h"
# include "trace.h"

t_canvas	canvas(int width, int height);
t_camera	camera(t_canvas *canvas, t_point3 orig, t_vec3 dir, double fov);

t_sphere	*sphere(t_point3 center, double radius);
t_cylinder	*cylinder(t_point3 center, double radius, t_vec3 dir,
				double height);
void		obj_add_cy_face(t_object **objs, t_object *cy_obj);
t_plane		*plane(t_point3 center, t_vec3 dir, double radius);
t_object	*object(t_object_type type, void *element, t_color3 albedo);

t_light		*light_point(t_point3 light_origin,
				t_color3 light_color, double bright_ratio);

void		world_init(t_object **world, t_parser *p);
void		parse_init_scene(t_mlx *info, char *scene_file);
void		raytrace_scene(t_mlx *info);
void		free_scene(t_scene *scene);

#endif
