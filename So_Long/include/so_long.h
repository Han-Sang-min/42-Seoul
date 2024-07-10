/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:47:52 by hansangmin        #+#    #+#             */
/*   Updated: 2022/10/02 19:34:28 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include "../mlx/mlx.h"

# define ERROR_CHECK 2
# define INIT_MLX 3
# define INIT_ELEMENT_CHECK 0b1111
# define WALL 0b1000
# define FEED 0b0100
# define EXIT 0b0010
# define PLAYER 0b0001
# define IMGSIZE 64
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17

typedef struct s_instance_ptr_set
{
	void	*init;
	void	*window;
}	t_instance_ptr_set;

typedef struct s_img_ptr_set
{
	void	*background;
	void	*packman_right;
	void	*packman_left;
	void	*packman_down;
	void	*packman_up;
	void	*exit;
	void	*feed;
	void	*game_end;
	void	*wall;
}	t_img_ptr_set;

typedef struct s_data_of_board
{
	int		height;
	int		width;
	int		columns;
	int		row;
	int		p_x;
	int		p_y;
	int		feed_size;
	int		cnt_press;
	char	*map;
}	t_data_of_board;

typedef struct s_img_coor
{
	int	x;
	int	y;
}	t_img_coor;

typedef struct s_set_of_struct
{
	t_data_of_board		*t_dob;
	t_img_ptr_set		*t_img_ps;
	t_instance_ptr_set	*t_inst_ps;
}	t_set_of_struct;

void	make_board(t_instance_ptr_set *t_inst_ps, \
t_img_ptr_set *t_img_ps, t_data_of_board *t_dogi);
void	init_mlx(t_instance_ptr_set *t_inst_ps, t_data_of_board *t_dob);
char	*read_map(char *file, char *map_array);
void	err_occur(int error_code);
void	err_occur_msg(char *msg);
void	error_check(int argc, t_data_of_board *t_dob);
int		key_press(int keycode, t_set_of_struct *t_sos);
void	load_img(t_instance_ptr_set *t_inst_ps, \
t_img_ptr_set *t_img_ps, t_data_of_board *t_dob);
void	init_sos(t_instance_ptr_set *t_inst_ps, t_img_ptr_set *t_img_ps, \
t_data_of_board *t_dob, t_set_of_struct *t_sos);
int		exit_game(t_set_of_struct *t_sos);

#endif