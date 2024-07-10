/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:58:40 by hansangmin        #+#    #+#             */
/*   Updated: 2022/10/02 20:53:05 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_mlx(t_instance_ptr_set *t_inst_ps, t_data_of_board *t_dob)
{
	t_inst_ps->init = mlx_init();
	if (!t_inst_ps->init)
		err_occur(INIT_MLX);
	t_inst_ps->window = mlx_new_window(t_inst_ps->init, \
	t_dob->row * IMGSIZE, (t_dob->columns) * IMGSIZE, "s0_long");
}

void	init_sos(t_instance_ptr_set *t_inst_ps, t_img_ptr_set *t_img_ps, \
t_data_of_board *t_dob, t_set_of_struct *t_sos)
{
	t_sos->t_inst_ps = t_inst_ps;
	t_sos->t_img_ps = t_img_ps;
	t_sos->t_dob = t_dob;
}
