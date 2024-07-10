/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:15:55 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:17:30 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef int				t_object_type;
# define SP 0
# define CY 1
# define PL 2
# define LIGHT_POINT 10

typedef int				t_bool;
# define FALSE 0
# define TRUE 1

# define EPSILON 1e-3
# define KSN 64
# define KS 2.0

struct	s_vec3
{
	double	x;
	double	y;
	double	z;
};

typedef struct s_vec3	t_vec3;
typedef struct s_vec3	t_point3;
typedef struct s_vec3	t_color3;

typedef struct s_scene	t_scene;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	t_scene	*scene;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_mlx;

typedef struct s_disc
{
	double	a;
	double	half_b;
	double	c;
	double	dcm;
}	t_disc;

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
}	t_ray;

typedef struct s_phong_light
{
	t_color3	diffuse;
	t_vec3		light_dir;
	double		kd;
	double		light_len;
	t_ray		light_ray;
	t_color3	specular;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		spec;
}	t_phong_light;

typedef struct s_camera
{
	t_point3	orig;
	t_vec3		dir;
	double		focal_len;
	double		viewport_h;
	double		viewport_w;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_point3	left_bottom;
}	t_camera;

typedef struct s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
}	t_canvas;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		tmin;
	double		tmax;
	double		t;
	t_bool		front_face;
	t_color3	albedo;
}	t_hit_record;

typedef struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
	t_color3		albedo;
}	t_object;

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
}	t_sphere;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		dir;
	double		radius;
	double		radius2;
	double		height;
}	t_cylinder;

typedef struct s_plane
{
	t_point3	center;
	t_vec3		dir;
	double		radius;
}	t_plane;

typedef struct s_light
{
	t_point3	origin;
	t_color3	light_color;
	double		bright_ratio;
}	t_light;

typedef struct s_scene
{
	t_canvas		canvas;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_color3		ambient;
	t_ray			ray;
	t_hit_record	rec;
}	t_scene;

typedef struct s_parser_ambient
{
	double		ratio;
	t_color3	rgb;
}	t_parser_ambient;

typedef struct s_parser_camera
{
	t_point3	view_point;
	t_vec3		orientation;
	double		fov;
}	t_parser_camera;

typedef struct s_parser_light
{
	t_point3	light_point;
	double		ratio;
	t_color3	rgb;
}	t_parser_light;

typedef struct s_parser_sp
{
	t_point3	center;
	double		diameter;
	t_color3	rgb;
}	t_parser_sp;

typedef struct s_parser_pl
{
	t_point3	coord;
	t_vec3		orientation;
	t_color3	rgb;
}	t_parser_pl;

typedef struct s_parser_cy
{
	t_point3	coord;
	t_vec3		orientation;
	double		diameter;
	double		height;
	t_color3	rgb;
}	t_parser_cy;

typedef struct s_parser
{
	t_parser_ambient	ambient_light;
	t_parser_camera		camera;
	t_parser_light		light;
	t_parser_sp			*spheres;
	t_parser_pl			*planes;
	t_parser_cy			*cylinders;
	int					s;
	int					p;
	int					cy;
}	t_parser;

#endif
