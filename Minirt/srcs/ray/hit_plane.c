/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:14:39 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:14:40 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_bool	hit_plane(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_plane	*pl;
	float	numerator;
	float	denominator;
	float	root;

	pl = obj->element;
	denominator = vdot(ray->dir, pl->dir);
	if (fabs(denominator) < EPSILON)
		return (FALSE);
	numerator = vdot(vminus(pl->center, ray->orig), pl->dir);
	root = numerator / denominator;
	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	if (pl->radius != INFINITY)
		if (vlength(vminus(pl->center, rec->p)) > pl->radius)
			return (FALSE);
	rec->normal = pl->dir;
	set_face_normal(ray, rec);
	rec->albedo = obj->albedo;
	return (TRUE);
}
