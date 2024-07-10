/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:35:13 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/16 14:19:13 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"

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

void	ko_exit(void)
{
	ft_printf("KO\n");
	exit(1);
}
