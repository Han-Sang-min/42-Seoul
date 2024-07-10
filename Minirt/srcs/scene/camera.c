/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:14:28 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:14:29 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_canvas	canvas(int width, int height)
{
	t_canvas	canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspect_ratio = (double)width / (double)height;
	return (canvas);
}

t_vec3	cam_set_vup(t_vec3 dir)
{
	if (dir.x == 0 && dir.y != 0 && dir.z == 0)
		return (vec3(0, dir.y, EPSILON));
	else
		return (vec3(0, 1, 0));
}

t_camera	camera(t_canvas *canvas, t_point3 orig, t_vec3 dir, double fov)
{
	t_camera	cam;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;

	cam.orig = orig;
	cam.focal_len = tan((fov * M_PI / 180.0) / 2.0);
	cam.viewport_h = cam.focal_len * 2;
	cam.viewport_w = cam.viewport_h * canvas->aspect_ratio;
	cam.dir = vunit(dir);
	w = vunit(vmult(dir, -1));
	u = vunit(vcross(cam_set_vup(dir), w));
	v = vcross(w, u);
	cam.horizontal = vmult(u, cam.viewport_w);
	cam.vertical = vmult(v, cam.viewport_h);
	cam.left_bottom = vminus(vminus(vminus(cam.orig,
					vdivide(cam.horizontal, 2)),
				vdivide(cam.vertical, 2)), w);
	return (cam);
}