/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:13:25 by wonbpark          #+#    #+#             */
/*   Updated: 2023/03/09 16:15:39 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "parser.h"

void	free_scene(t_scene *scene)
{
	t_object	*temp;
	t_object	*head;

	head = scene->world;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->element);
		free(temp);
	}
	free(scene->light->element);
	free(scene->light);
	free(scene);
}

void	parse_init_scene(t_mlx *info, char *scene_file)
{
	t_scene		*scene;
	t_object	*world;
	t_parser	p;

	parser_init(&p, scene_file);
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (scene == NULL)
		exit_error("scene malloc failed");
	scene->canvas = canvas(WIDTH, HEIGHT);
	scene->camera = camera(&scene->canvas, p.camera.view_point, \
	p.camera.orientation, p.camera.fov);
	world = NULL;
	world_init(&world, &p);
	scene->world = world;
	scene->light = object(LIGHT_POINT, light_point(p.light.light_point, \
	vdivide(p.light.rgb, 255), p.light.ratio), color3(0, 0, 0));
	scene->ambient = vmult(vdivide(p.ambient_light.rgb, 255), \
	p.ambient_light.ratio);
	free_parser(&p);
	info->scene = scene;
}
