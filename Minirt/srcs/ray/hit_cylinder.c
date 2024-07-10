/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:14:36 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:14:36 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

static t_bool	cy_boundary(t_cylinder *cy, t_vec3 at_point, double *hit_height)
{
	*hit_height = vdot(vminus(at_point, cy->center), cy->dir);
	if (*hit_height > cy->height || *hit_height < 0)
		return (FALSE);
	return (TRUE);
}

static t_vec3	get_cylinder_normal(t_cylinder *cy, t_vec3 at_point,
	double hit_height)
{
	t_point3	hit_center;
	t_vec3		normal;

	hit_center = vplus(cy->center, vmult(cy->dir, hit_height));
	normal = vminus(at_point, hit_center);
	return (vunit(normal));
}

static t_disc	calc_cy_disc(t_cylinder *cy, t_ray *ray)
{
	t_disc	disc;
	t_vec3	oc;

	oc = vminus(ray->orig, cy->center);
	disc.a = vlength2(vcross(ray->dir, cy->dir));
	disc.half_b = vdot(vcross(ray->dir, cy->dir), vcross(oc, cy->dir));
	disc.c = vlength2(vcross(oc, cy->dir)) - pow(cy->radius, 2);
	disc.dcm = disc.half_b * disc.half_b - disc.a * disc.c;
	return (disc);
}

static double	calc_root(t_disc disc, double sqrtd, double tmin, double tmax)
{
	double	root;

	root = (-disc.half_b - sqrtd) / disc.a;
	if (root < tmin || tmax < root)
	{
		root = (-disc.half_b + sqrtd) / disc.a;
		if (root < tmin || tmax < root)
			return (0);
	}
	return (root);
}

int	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	t_disc		disc;
	double		sqrtd;
	double		root;
	double		hit_height;

	cy = cy_obj->element;
	disc = calc_cy_disc(cy, ray);
	if (disc.dcm < 0)
		return (0);
	sqrtd = sqrt(disc.dcm);
	root = calc_root(disc, sqrtd, rec->tmin, rec->tmax);
	if (root == 0)
		return (0);
	if (!(cy_boundary(cy, ray_at(ray, root), &hit_height)))
		return (0);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = get_cylinder_normal(cy, rec->p, hit_height);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (1);
}
