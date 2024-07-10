/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:31:10 by hansangmin        #+#    #+#             */
/*   Updated: 2022/11/16 16:00:27 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	swap_node(t_stack *node1, t_stack *node2)
{
	int	tmp;

	tmp = node1->data;
	node1->data = node2->data;
	node2->data = tmp;
}

int	cnt_element(t_stack *top)
{
	int	ret;

	ret = 0;
	while (top)
	{
		top = top->prev;
		ret++;
	}
	return (ret);
}

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	err_exit(void)
{
	ft_printf("Error\n");
	exit(1);
}

int	is_need_rot(t_sort_info *tsi, t_set_of_tb *sot)
{
	t_stack	*tmp;

	tmp = sot->top_b;
	while (tmp)
	{
		if (tmp->data < tsi->pv1)
			return (1);
		tmp = tmp->prev;
	}
	return (0);
}
