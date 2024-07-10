/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 04:29:19 by hansangmin        #+#    #+#             */
/*   Updated: 2022/10/02 20:53:09 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	exit_game(t_set_of_struct *t_sos)
{
	mlx_destroy_window(t_sos->t_inst_ps->init, t_sos->t_inst_ps->window);
	free(t_sos->t_dob->map);
	exit(0);
}

void	press_proc(int pos, t_set_of_struct *t_sos, int key)
{
	t_data_of_board		*t_dob;
	t_instance_ptr_set	*t_inst_ps;
	t_img_ptr_set		*t_img_ps;

	t_dob = t_sos->t_dob;
	t_inst_ps = t_sos->t_inst_ps;
	t_img_ps = t_sos->t_img_ps;
	if (t_dob->map[pos] == '1')
		return ;
	if (t_dob->map[pos] == 'C')
	{
		t_dob->map[pos] = '0';
		t_dob->feed_size--;
	}
	if (t_dob->map[pos] == 'E' && t_dob->feed_size == 0)
		exit(0);
	if (key == KEY_W)
		t_dob->p_y--;
	else if (key == KEY_A)
		t_dob->p_x--;
	else if (key == KEY_S)
		t_dob->p_y++;
	else if (key == KEY_D)
		t_dob->p_x++;
	make_board(t_inst_ps, t_img_ps, t_dob);
}

int	key_press(int keycode, t_set_of_struct *t_sos)
{
	int				pos;
	t_data_of_board	*t_dob;

	t_dob = t_sos->t_dob;
	if (keycode == KEY_W)
		pos = (t_dob->p_y - 1) * (t_dob->row + 1) + t_dob->p_x;
	else if (keycode == KEY_A)
		pos = t_dob->p_y * (t_dob->row + 1) + (t_dob->p_x - 1);
	else if (keycode == KEY_S)
		pos = (t_dob->p_y + 1) * (t_dob->row + 1) + t_dob->p_x;
	else if (keycode == KEY_D)
		pos = t_dob->p_y * (t_dob->row + 1) + (t_dob->p_x + 1);
	else if (keycode == KEY_ESC)
		exit (0);
	else
		return (0);
	press_proc(pos, t_sos, keycode);
	if (t_dob->map[pos] != '1')
		printf("move : %d\n", ++t_dob->cnt_press);
	return (0);
}
