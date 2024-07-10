/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:38:23 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/15 20:53:36 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"

void	push_data(t_set_of_tb *sot, char *data)
{
	t_stack	*new_part_of_list;

	new_part_of_list = (t_stack *)malloc(sizeof(t_stack));
	if (!new_part_of_list)
		exit(1);
	digit_check(data);
	max_check(data);
	dup_check(sot->top_a, data);
	new_part_of_list->data = ft_atoi(data);
	new_part_of_list->prev = NULL;
	new_part_of_list->next = NULL;
	if (!sot->bot_a)
	{
		sot->top_a = new_part_of_list;
		sot->bot_a = new_part_of_list;
		return ;
	}
	new_part_of_list->next = sot->bot_a;
	sot->bot_a->prev = new_part_of_list;
	sot->bot_a = new_part_of_list;
}

void	init_stack(t_set_of_tb *sot, int total_element, char **data)
{
	int	nu;

	nu = 0;
	digit_check(data[1]);
	while (++nu < total_element)
		push_data(sot, data[nu]);
}
