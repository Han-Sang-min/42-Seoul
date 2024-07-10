/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:14:28 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:14:29 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "minirt.h"
#include "utils.h"
#include "scene.h"

t_object	*object(t_object_type type, void *element, t_color3 albedo)
{
	t_object	*new;

	new = (t_object *)malloc(sizeof(t_object));
	if (new == NULL)
		exit_error("FATAL: Malloc failure");
	new->type = type;
	new->element = element;
	new->next = NULL;
	new->albedo = albedo;
	return (new);
}

t_sphere	*sphere(t_point3 center, double radius)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		exit_error("FATAL: Malloc failure");
	sphere->center = center;
	sphere->radius = radius;
	sphere->radius2 = radius * radius;
	return (sphere);
}

t_cylinder	*cylinder(t_point3 center, double radius, t_vec3 dir, double height)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		exit_error("FATAL: Malloc failure");
	cylinder->center = center;
	cylinder->dir = vunit(dir);
	cylinder->radius = radius;
	cylinder->height = height;
	return (cylinder);
}

t_plane	*plane(t_point3 center, t_vec3 dir, double radius)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (plane == NULL)
		exit_error("FATAL: Malloc failure");
	plane->center = center;
	plane->dir = vunit(dir);
	plane->radius = radius;
	return (plane);
}

t_light	*light_point(t_point3 light_origin, t_color3 light_color,
	double bright_ratio)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (light == NULL)
		exit_error("FATAL: Malloc failure");
	light->origin = light_origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}
