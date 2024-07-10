/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:20:52 by hansangmin        #+#    #+#             */
/*   Updated: 2022/11/13 09:07:00 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	sort_size3(t_set_of_tb *sot)
{
	if (sot->bot_a->data < sot->top_a->data \
	&& sot->bot_a->next->data < sot->top_a->data)
		cmd_execute("ra", sot);
	else if (sot->bot_a->data < sot->bot_a->next->data)
		cmd_execute("rra", sot);
	if (sot->top_a->prev->data < sot->top_a->data)
		cmd_execute("sa", sot);
}

void	sort_size5(t_set_of_tb *sot, t_schedules **schd)
{
	t_sort_info	tsi;
	int			idx;

	idx = -1;
	if ((*schd)->size == 5)
	{
		tsi = find_pivot(*schd, sot);
		while (++idx < (*schd)->size)
		{
			if (tsi.pv2 <= sot->top_a->data)
				cmd_execute("ra", sot);
			else if (tsi.pv1 <= sot->top_a->data)
				cmd_execute("pb", sot);
			else
			{
				cmd_execute("pb", sot);
				cmd_execute("rb", sot);
			}
		}
		pop_schd(schd);
		push_schd(schd, tsi.size1, 'B');
		push_schd(schd, tsi.size2, 'B');
		push_schd(schd, tsi.size3, 'A');
	}
	sort_stack(sot, schd);
}

void	sort_stack_a(t_set_of_tb *sot, t_schedules **schd)
{
	t_sort_info	tsi;

	if ((*schd)->size > 4)
	{
		sort_out_a1(&tsi, sot, *schd);
		a_rot(tsi, sot);
		pop_schd(schd);
		push_schd(schd, tsi.size1, 'B');
		push_schd(schd, tsi.size2, 'B');
		push_schd(schd, tsi.size3, 'A');
	}
	else
	{
		sort_out_a2(sot, *schd);
		pop_schd(schd);
	}
}

void	sort_stack_b(t_set_of_tb *sot, t_schedules **schd)
{
	t_sort_info	tsi;

	if ((*schd)->size > 4)
	{
		sort_out_b1(&tsi, sot, *schd);
		pop_schd(schd);
		push_schd(schd, tsi.size1, 'B');
		push_schd(schd, tsi.size2, 'A');
		push_schd(schd, 0, 'R');
		push_schd(schd, tsi.size3, 'A');
	}
	else
	{
		sort_out_b2(sot, *schd);
		pop_schd(schd);
	}
}

void	sort_stack(t_set_of_tb *sot, t_schedules **schd)
{
	if (!*schd)
		return ;
	if ((*schd)->point == 'R')
	{
		b_rot((*schd)->next->size, (*schd)->next->next->size, sot);
		pop_schd(schd);
	}
	else if ((*schd)->point == 'A')
		sort_stack_a(sot, schd);
	else if ((*schd)->point == 'B')
		sort_stack_b(sot, schd);
	sort_stack(sot, schd);
}
