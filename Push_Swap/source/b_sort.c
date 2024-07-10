/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:59:38 by hansangmin        #+#    #+#             */
/*   Updated: 2022/11/16 15:55:09 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	b_size4(t_set_of_tb *sot)
{
	cmd_execute("pa", sot);
	cmd_execute("pa", sot);
	if (sot->top_b->data < sot->top_b->prev->data)
		cmd_execute("sb", sot);
	if (sot->top_a->data > sot->top_a->prev->data)
		cmd_execute("sa", sot);
	cmd_execute("ra", sot);
	cmd_execute("ra", sot);
	b_size3_4(sot, 2, 2);
}

void	b_size3(t_set_of_tb *sot)
{
	cmd_execute("pa", sot);
	cmd_execute("pa", sot);
	if (sot->top_a->data > sot->top_a->prev->data)
		cmd_execute("sa", sot);
	cmd_execute("ra", sot);
	cmd_execute("ra", sot);
	b_size3_4(sot, 2, 1);
}

void	sort_out_b2(t_set_of_tb *sot, t_schedules *schd)
{
	if (schd->size == 4)
		b_size4(sot);
	else if (schd->size == 3)
		b_size3(sot);
	else if (schd->size == 2)
	{
		if (sot->top_b->data < sot->top_b->prev->data)
			cmd_execute("sb", sot);
		cmd_execute("pa", sot);
		cmd_execute("pa", sot);
	}
	else
		cmd_execute("pa", sot);
}

void	sort_out_b1(t_sort_info *tsi, t_set_of_tb *sot, t_schedules *schd)
{
	int	idx;

	idx = -1;
	*tsi = find_pivot(schd, sot);
	while (++idx < schd->size)
	{
		if (tsi->pv2 <= sot->top_b->data)
			cmd_execute("pa", sot);
		else if (tsi->pv1 <= sot->top_b->data)
		{
			cmd_execute("pa", sot);
			if (is_need_rot(tsi, sot))
				cmd_execute("ra", sot);
		}
		else
			cmd_execute("rb", sot);
	}
}

void	b_rot(int size2, int size1, t_set_of_tb *sot)
{
	while (size2 || size1)
	{
		if (size2 && size2--)
			cmd_execute("rra", sot);
		if (size1 && size1--)
			cmd_execute("rrb", sot);
	}
}
