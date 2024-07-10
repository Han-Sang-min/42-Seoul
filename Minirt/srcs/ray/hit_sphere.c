/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:14:42 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:14:43 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

static t_disc	calc_sp_disc(t_sphere *sp, t_ray *ray)
{
	t_disc	disc;
	t_vec3	oc;

	oc = vminus(ray->orig, sp->center);
	disc.a = vlength2(ray->dir);
	disc.half_b = vdot(oc, ray->dir);
	disc.c = vlength2(oc) - sp->radius2;
	disc.dcm = disc.half_b * disc.half_b - disc.a * disc.c;
	return (disc);
}

t_bool	hit_sphere(t_object *object, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
	t_disc		disc;
	double		sqrtd;
	double		root;

	sp = (t_sphere *)object->element;
	disc = calc_sp_disc(sp, ray);
	if (disc.dcm < 0)
		return (FALSE);
	sqrtd = sqrt(disc.dcm);
	root = (-(disc.half_b) - sqrtd) / disc.a;
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-(disc.half_b) + sqrtd) / disc.a;
		if (root < rec->tmin || root > rec->tmax)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vunit(vminus(rec->p, sp->center));
	set_face_normal(ray, rec);
	rec->albedo = object->albedo;
	return (TRUE);
}
