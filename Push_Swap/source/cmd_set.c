/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:52:36 by hansangmin        #+#    #+#             */
/*   Updated: 2022/11/16 16:21:07 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	cmd_pnt2(char *cmd, char save[4])
{
	if ((!ft_strncmp(save, "rra", 3) && !ft_strncmp(cmd, "rrb", 3)) \
	|| (!ft_strncmp(save, "rrb", 3) && !ft_strncmp(cmd, "rra", 3)))
	{
		ft_printf("rrr\n");
		*save = 0;
	}
	else if ((!ft_strncmp(save, "pa", 3) && !ft_strncmp(cmd, "pb", 3)) \
	|| (!ft_strncmp(save, "pb", 3) && !ft_strncmp(cmd, "pa", 3)))
		*save = 0;
	else if ((!ft_strncmp(save, "ra", 3) && !ft_strncmp(cmd, "rra", 3)) \
	|| (!ft_strncmp(save, "rra", 3) && !ft_strncmp(cmd, "ra", 3)))
		*save = 0;
	else if (!ft_strncmp(save, "end", 3))
		ft_printf("%s\n", save);
	else
	{
		ft_printf("%s\n", save);
		ft_strlcpy(save, cmd, 4);
	}
}

void	cmd_pnt(char *cmd)
{
	static char	save[4];

	if (!cmd)
		return ;
	if (!*save)
	{
		ft_strlcpy(save, cmd, 4);
		return ;
	}
	if ((!ft_strncmp(save, "sa", 3) && !ft_strncmp(cmd, "sb", 3)) \
	|| (!ft_strncmp(save, "sb", 3) && !ft_strncmp(cmd, "sa", 3)))
	{
		ft_printf("ss\n");
		*save = 0;
	}
	else if ((!ft_strncmp(save, "ra", 3) && !ft_strncmp(cmd, "rb", 3)) \
	|| (!ft_strncmp(save, "rb", 3) && !ft_strncmp(cmd, "ra", 3)))
	{
		ft_printf("rr\n");
		*save = 0;
	}
	else
		cmd_pnt2(cmd, save);
}

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
			cmd = NULL;
		else
			cmd_rotate(&sot->top_a, &sot->bot_a);
	}
	else if (!ft_strncmp(cmd, "rb", 3))
	{
		if (sot->top_b->data == sot->bot_b->data)
			cmd = NULL;
		else
			cmd_rotate(&sot->top_b, &sot->bot_b);
	}
	else
		cmd_execute_part(cmd, sot);
	cmd_pnt(cmd);
}
