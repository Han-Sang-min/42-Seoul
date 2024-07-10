/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_detail_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:25:05 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/15 21:54:24 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"

void	cmd_swap(t_stack *top)
{
	if (cnt_element(top) > 1)
		swap_node(top, top->prev);
}

void	cmd_push(t_stack **dest, t_stack **bottom, t_stack **src)
{
	t_stack	*tmp;

	if (*src != NULL)
	{
		tmp = *src;
		*src = (*src)->prev;
		if (*src)
			(*src)->next = NULL;
		tmp->prev = *dest;
		if (*dest != NULL)
			(*dest)->next = tmp;
		else
			*bottom = tmp;
		*dest = tmp;
	}
}

void	cmd_rotate(t_stack **top, t_stack **bottom)
{
	t_stack	*tmp;

	if (*top != NULL && *top != *bottom)
	{
		tmp = *top;
		*top = (*top)->prev;
		(*top)->next = NULL;
		tmp->prev = NULL;
		tmp->next = *bottom;
		(*bottom)->prev = tmp;
		*bottom = tmp;
	}
}

void	cmd_reverse_rotate(t_stack **top, t_stack **bottom)
{
	t_stack	*tmp;

	if (*top != NULL && *top != *bottom)
	{
		tmp = *bottom;
		*bottom = (*bottom)->next;
		(*bottom)->prev = NULL;
		tmp->next = NULL;
		tmp->prev = *top;
		(*top)->next = tmp;
		*top = tmp;
	}
}
