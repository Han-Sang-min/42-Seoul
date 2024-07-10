/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:15:52 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:15:53 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include "structures.h"
# include "utils.h"
# include "scene.h"
# include "trace.h"
# include "mlx.h"

# define WIDTH 960
# define HEIGHT 640

# define DESTROY_NOTIFY 17
# define KEYPRESS 2

# define ESC 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2

void	exit_error(const char *msg);

void	init_mlx(t_mlx *info);
int		exit_program(t_mlx *info);
int		key_hook(int keycode, t_mlx *info);

#endif
