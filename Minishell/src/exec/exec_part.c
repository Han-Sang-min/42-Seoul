/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:19:40 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 10:11:28 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	common_part(t_info *cur_info)
{
	char	*cmd;

	set_redir(cur_info);
	if (builtin_check(cur_info))
	{
		cmd = parsing_cmd(cur_info->cmd);
		if (execve(cmd, cur_info->av, *g_var.environ) == -1)
			err_exit("no such file or directory");
	}
}

void	execute_middle_cmd(t_info *cur_info)
{
	ft_close(cur_info->fds[OUT][IN]);
	common_part(cur_info);
}

void	execute_last_cmd(t_info *cur_info)
{
	common_part(cur_info);
}
