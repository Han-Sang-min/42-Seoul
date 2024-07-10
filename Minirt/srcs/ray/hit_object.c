/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:14:37 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:14:38 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_bool	hit(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_flag;
	t_hit_record	tmp;

	tmp = *rec;
	hit_flag = FALSE;
	while (obj != NULL)
	{
		if (hit_obj(obj, ray, &tmp))
		{
			hit_flag = TRUE;
			tmp.tmax = tmp.t;
			*rec = tmp;
		}
		obj = obj->next;
	}
	return (hit_flag);
}

t_bool	hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_flag;

	hit_flag = FALSE;
	if (obj->type == SP)
		hit_flag = hit_sphere(obj, ray, rec);
	else if (obj->type == CY)
		hit_flag = hit_cylinder(obj, ray, rec);
	else if (obj->type == PL)
		hit_flag = hit_plane(obj, ray, rec);
	return (hit_flag);
}

void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	rec->front_face = vdot(r->dir, rec->normal) < 0;
	if (rec->front_face)
		rec->normal = rec->normal;
	else
		rec->normal = vmult(rec->normal, -1);
}
