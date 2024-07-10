/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:14:53 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:14:54 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	recenter_cam(t_vec3 *result, t_vec3 *a, t_vec3 *b)
{
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	result->z = a->z - b->z;
}

int	key_hook(int keycode, t_mlx *info)
{
	t_vec3	vec;

	if (keycode == ESC)
		exit_program(info);
	if (keycode == W_KEY)
		vset(&vec, 0, 0.1, 0);
	if (keycode == A_KEY)
		vset(&vec, 0.1, 0, 0);
	if (keycode == S_KEY)
		vset(&vec, 0, -0.1, 0);
	if (keycode == D_KEY)
		vset(&vec, -0.1, 0, 0);
	recenter_cam(&info->scene->camera.orig, &info->scene->camera.orig, &vec);
	raytrace_scene(info);
	return (0);
}

void	init_mlx(t_mlx *info)
{
	info->mlx_ptr = mlx_init();
	info->win_ptr = mlx_new_window(info->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	info->img.img_ptr = mlx_new_image(info->mlx_ptr, WIDTH, HEIGHT);
	info->img.addr = mlx_get_data_addr(info->img.img_ptr, &info->img.bpp,
			&info->img.line_len, &info->img.endian);
}
