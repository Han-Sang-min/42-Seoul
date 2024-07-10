/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:15:06 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:15:10 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exit_program(t_mlx *info)
{
	free_scene(info->scene);
	mlx_destroy_image(info->mlx_ptr, info->img.img_ptr);
	mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	//system("leaks miniRT");
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx	info;

	if (ac != 2)
		exit_error("Error: argument must be one [scene].rt file");
	parse_init_scene(&info, av[1]);
	init_mlx(&info);
	raytrace_scene(&info);
	mlx_hook(info.win_ptr, DESTROY_NOTIFY, 0, exit_program, &info);
	mlx_hook(info.win_ptr, KEYPRESS, 1L << 0, key_hook, &info);
	mlx_loop(info.mlx_ptr);
}
