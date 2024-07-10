/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:53:36 by hansangmin        #+#    #+#             */
/*   Updated: 2022/10/02 20:53:19 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	load_img(t_instance_ptr_set *t_inst_ps, \
t_img_ptr_set *t_img_ps, t_data_of_board *t_dob)
{
	t_img_ps->background = mlx_xpm_file_to_image(t_inst_ps->init, \
	"./images/background.xpm", &t_dob->width, &t_dob->height);
	t_img_ps->game_end = mlx_xpm_file_to_image(t_inst_ps->init, \
	"./images/game_end.xpm", &t_dob->width, &t_dob->height);
	t_img_ps->packman_right = mlx_xpm_file_to_image(t_inst_ps->init, \
	"./images/packman_right.xpm", &t_dob->width, &t_dob->height);
	t_img_ps->exit = mlx_xpm_file_to_image(t_inst_ps->init, \
	"./images/exit.xpm", &t_dob->width, &t_dob->height);
	t_img_ps->feed = mlx_xpm_file_to_image(t_inst_ps->init, \
	"./images/feed.xpm", &t_dob->width, &t_dob->height);
	t_img_ps->wall = mlx_xpm_file_to_image(t_inst_ps->init, \
	"./images/wall.xpm", &t_dob->width, &t_dob->height);
}

void	pnt_map(t_instance_ptr_set *t_inst_ps, \
t_img_ptr_set *t_img_ps, t_img_coor *t_ic, char div_img)
{
	if (div_img == '0')
		mlx_put_image_to_window(t_inst_ps->init, t_inst_ps->window, \
		t_img_ps->background, IMGSIZE * t_ic->x, IMGSIZE * t_ic->y);
	if (div_img == '1')
		mlx_put_image_to_window(t_inst_ps->init, t_inst_ps->window, \
		t_img_ps->wall, IMGSIZE * t_ic->x, IMGSIZE * t_ic->y);
	if (div_img == 'C')
		mlx_put_image_to_window(t_inst_ps->init, t_inst_ps->window, \
		t_img_ps->feed, IMGSIZE * t_ic->x, IMGSIZE * t_ic->y);
	if (div_img == 'E')
	{
		mlx_put_image_to_window(t_inst_ps->init, t_inst_ps->window, \
		t_img_ps->background, IMGSIZE * t_ic->x, IMGSIZE * t_ic->y);
		mlx_put_image_to_window(t_inst_ps->init, t_inst_ps->window, \
		t_img_ps->exit, IMGSIZE * t_ic->x, IMGSIZE * t_ic->y);
	}
}

void	make_board(t_instance_ptr_set *t_inst_ps, \
t_img_ptr_set *t_img_ps, t_data_of_board *t_dob)
{
	int			idx;
	int			nc;
	t_img_coor	t_ic;

	idx = -1;
	nc = 0;
	while (t_dob->map[++idx])
	{
		if (t_dob->map[idx] == '\n')
			nc++;
		t_ic.x = (idx - nc) % t_dob->row;
		t_ic.y = (idx - nc) / t_dob->row;
		pnt_map(t_inst_ps, t_img_ps, &t_ic, t_dob->map[idx]);
		if (t_dob->map[idx] == 'P')
		{
			t_dob->p_x = t_ic.x;
			t_dob->p_y = t_ic.y;
			t_dob->map[idx] = '0';
		}
	}
	mlx_put_image_to_window(t_inst_ps->init, t_inst_ps->window, \
		t_img_ps->packman_right, IMGSIZE * t_dob->p_x, IMGSIZE * t_dob->p_y);
}
