/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 00:22:27 by hansangmin        #+#    #+#             */
/*   Updated: 2022/11/16 15:50:16 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	a_size4(t_set_of_tb *sot)
{
	cmd_execute("pb", sot);
	cmd_execute("pb", sot);
	if (sot->top_b->data < sot->top_b->prev->data)
		cmd_execute("sb", sot);
	if (sot->top_a->data > sot->top_a->prev->data)
		cmd_execute("sa", sot);
	cmd_execute("ra", sot);
	cmd_execute("ra", sot);
	a_size3_4(sot, 2, 2);
}

void	a_size3(t_set_of_tb *sot)
{
	cmd_execute("pb", sot);
	if (sot->top_a->data > sot->top_a->prev->data)
		cmd_execute("sa", sot);
	if (sot->bot_a->next->data != sot->top_a->data)
	{
		cmd_execute("ra", sot);
		cmd_execute("ra", sot);
	}
	a_size3_4(sot, 2, 1);
}

void	sort_out_a2(t_set_of_tb *sot, t_schedules *schd)
{
	if (schd->size == 4)
		a_size4(sot);
	else if (schd->size == 3)
		a_size3(sot);
	else if (schd->size == 2)
	{
		if (sot->top_a->data > sot->top_a->prev->data)
			cmd_execute("sa", sot);
	}
}

void	sort_out_a1(t_sort_info *tsi, t_set_of_tb *sot, t_schedules *schd)
{
	int	idx;

	idx = -1;
	*tsi = find_pivot(schd, sot);
	while (++idx < schd->size)
	{
		if (tsi->pv2 <= sot->top_a->data)
			cmd_execute("ra", sot);
		else if (tsi->pv1 <= sot->top_a->data)
		{
			cmd_execute("pb", sot);
			cmd_execute("rb", sot);
		}
		else
			cmd_execute("pb", sot);
	}
}

void	a_rot(t_sort_info tsi, t_set_of_tb *sot)
{
	while (tsi.size3 || tsi.size2)
	{
		if (tsi.size3 && tsi.size3--)
			cmd_execute("rra", sot);
		if (tsi.size2 && tsi.size2--)
			cmd_execute("rrb", sot);
	}
}
