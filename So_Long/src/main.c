/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:22:38 by hansangmin        #+#    #+#             */
/*   Updated: 2022/10/02 20:53:15 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char *argv[])
{
	t_instance_ptr_set		t_inst_ps;
	t_img_ptr_set			t_img_ps;
	t_data_of_board			t_dob;
	t_set_of_struct			t_sos;

	t_dob.feed_size = 0;
	t_dob.cnt_press = 0;
	t_dob.columns = 0;
	t_dob.row = 0;
	t_dob.map = read_map(argv[1], t_dob.map);
	error_check(argc, &t_dob);
	init_mlx(&t_inst_ps, &t_dob);
	load_img(&t_inst_ps, &t_img_ps, &t_dob);
	make_board(&t_inst_ps, &t_img_ps, &t_dob);
	init_sos(&t_inst_ps, &t_img_ps, &t_dob, &t_sos);
	mlx_hook(t_inst_ps.window, EVENT_KEY_PRESS, 0, &key_press, &t_sos);
	mlx_hook(t_inst_ps.window, X_EVENT_KEY_EXIT, 0, &exit_game, &t_sos);
	mlx_loop(t_inst_ps.init);
	free(t_dob.map);
	return (0);
}
