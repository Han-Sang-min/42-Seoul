/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_cmd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:08:03 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/15 21:59:10 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"

void	del_newline(char *cmd)
{
	while (*cmd != '\n' && *cmd != '\0')
		cmd++;
	*cmd = '\0';
}

void	receive_cmd(t_set_of_tb *sot)
{
	char	*cmd;

	while (1)
	{
		cmd = get_next_line(0);
		if (!cmd)
			return ;
		del_newline(cmd);
		cmd_execute(cmd, sot);
	}
}
