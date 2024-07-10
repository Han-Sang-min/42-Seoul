/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:14:30 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:14:31 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "minirt.h"
#include "utils.h"
#include "scene.h"

void	obj_add_cy_face(t_object **objs, t_object *cy_obj)
{
	t_cylinder	*cy;
	t_plane		*top;
	t_plane		*bottom;

	cy = cy_obj->element;
	top = plane(cy->center, cy->dir, cy->radius);
	bottom = plane(vplus(cy->center, vmult(cy->dir, cy->height)),
			cy->dir, cy->radius);
	obj_add(objs, object(PL, top, cy_obj->albedo));
	obj_add(objs, object(PL, bottom, cy_obj->albedo));
}

void	obj_add(t_object **objects, t_object *new)
{
	t_object	*curr;

	if (*objects == NULL)
	{
		*objects = new;
		if (new->type == CY)
			obj_add_cy_face(objects, new);
		return ;
	}
	curr = *objects;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	if (new->type == CY)
		obj_add_cy_face(objects, new);
}

t_object	*obj_last(t_object *objects)
{
	if (objects == NULL)
		return (NULL);
	while (objects->next)
		objects = objects->next;
	return (objects);
}
