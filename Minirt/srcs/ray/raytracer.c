/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:14:27 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:14:27 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "parser.h"

void	world_init(t_object **world, t_parser *p)
{
	int	i;

	i = 0;
	while (i < p->s)
	{
		obj_add(world, object(SP, sphere(p->spheres[i].center, \
		p->spheres[i].diameter / 2), vdivide(p->spheres[i].rgb, 255)));
		i++;
	}
	i = 0;
	while (i < p->p)
	{
		obj_add(world, object(PL, plane(p->planes[i].coord, \
		p->planes[i].orientation, INFINITY), vdivide(p->planes[i].rgb, 255)));
		i++;
	}
	i = 0;
	while (i < p->cy)
	{
		obj_add(world, object(CY, cylinder(p->cylinders[i].coord, \
		p->cylinders[i].diameter / 2, p->cylinders[i].orientation, \
		p->cylinders[i].height), vdivide(p->cylinders[i].rgb, 255)));
		i++;
	}
}

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	raytrace_scene(t_mlx *info)
{
	int			i;
	int			j;
	double		u;
	double		v;
	t_color3	pixel_color;

	j = -1;
	while (++j < info->scene->canvas.height)
	{
		i = -1;
		while (++i < info->scene->canvas.width)
		{
			u = (double)i / (info->scene->canvas.width - 1);
			v = (double)j / (info->scene->canvas.height - 1);
			info->scene->ray = ray_primary(&info->scene->camera, u, v);
			pixel_color = ray_color(info->scene);
			my_mlx_pixel_put(&info->img, i, info->scene->canvas.height - j - 1,
				encode_color(pixel_color));
		}
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img.img_ptr, 0, 0);
}
