/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:40 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/15 22:03:12 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"

void	cmd_execute_part(char *cmd, t_set_of_tb *sot)
{
	if (!ft_strncmp(cmd, "ss", 3))
	{
		cmd_swap(sot->top_a);
		cmd_swap(sot->top_b);
	}
	else if (!ft_strncmp(cmd, "pa", 3))
		cmd_push(&sot->top_a, &sot->bot_a, &sot->top_b);
	else if (!ft_strncmp(cmd, "pb", 3))
		cmd_push(&sot->top_b, &sot->bot_b, &sot->top_a);
	else if (!ft_strncmp(cmd, "rr", 3))
	{
		cmd_rotate(&sot->top_a, &sot->bot_a);
		cmd_rotate(&sot->top_b, &sot->bot_b);
	}
	else if (!ft_strncmp(cmd, "rra", 3))
		cmd_reverse_rotate(&sot->top_a, &sot->bot_a);
	else if (!ft_strncmp(cmd, "rrb", 3))
		cmd_reverse_rotate(&sot->top_b, &sot->bot_b);
	else if (!ft_strncmp(cmd, "rrr", 3))
	{
		cmd_reverse_rotate(&sot->top_a, &sot->bot_a);
		cmd_reverse_rotate(&sot->top_b, &sot->bot_b);
	}
	else
		err_exit();
}

void	cmd_execute(char *cmd, t_set_of_tb *sot)
{
	if (!ft_strncmp(cmd, "sa", 3))
		cmd_swap(sot->top_a);
	else if (!ft_strncmp(cmd, "sb", 3))
		cmd_swap(sot->top_b);
	else if (!ft_strncmp(cmd, "ra", 3))
	{
		if (sot->top_a->data == sot->bot_a->data)
			return ;
		else
			cmd_rotate(&sot->top_a, &sot->bot_a);
	}
	else if (!ft_strncmp(cmd, "rb", 3))
	{
		if (sot->top_b->data == sot->bot_b->data)
			return ;
		else
			cmd_rotate(&sot->top_b, &sot->bot_b);
	}
	else
		cmd_execute_part(cmd, sot);
}
