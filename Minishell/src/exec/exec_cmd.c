/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:03:38 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 10:34:16 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_info(t_info *cur_info)
{
	cur_info->fds[OUT][OUT] = dup(STDOUT_FILENO);
	if (cur_info->fds[OUT][OUT] == -1)
		err_exit("dup err");
}

int	make_proc(int id, t_info **cur_info)
{
	const t_info	*head = *cur_info;

	while (*cur_info)
	{
		init_info(*cur_info);
		if ((*cur_info)->pipe)
			ft_pipe((*cur_info)->fds[OUT]);
		(*cur_info)->stat.pid = fork();
		if ((*cur_info)->stat.pid < 0)
			err_exit("fork fail");
		else if ((*cur_info)->stat.pid == 0)
			return (id);
		else if ((*cur_info)->next != NULL)
		{
			ft_close((*cur_info)->fds[IN][IN]);
			(*cur_info)->next->fds[IN][IN] = (*cur_info)->fds[OUT][IN];
			(*cur_info)->next->fds[IN][OUT] = (*cur_info)->fds[OUT][OUT];
			ft_close((*cur_info)->next->fds[IN][OUT]);
		}
		else
		{
			ft_close((*cur_info)->fds[IN][IN]);
			ft_close((*cur_info)->fds[OUT][OUT]);
		}
		id++;
		*cur_info = (*cur_info)->next;
	}
	*cur_info = (t_info *)head;
	return (-1);
}

void	proc_line(t_info *cur_info)
{
	if (cur_info->next == NULL)
		execute_last_cmd(cur_info);
	else
		execute_middle_cmd(cur_info);
}

int	wait_all_proc(t_info *root_info)
{
	int	ret;

	ret = 0;
	while (root_info)
	{
		ret = waitpid(root_info->stat.pid, &root_info->stat.stat, WNOHANG);
		if (ret == 0)
			break ;
		root_info = root_info->next;
	}
	return (ret);
}

void	exec_cmd(t_info *cur_info)
{
	init_child_signal_handler();
	cur_info->fds[IN][IN] = dup(STDIN_FILENO);
	if (!cur_info->fds[IN][IN])
		err_exit("dup error");
	cur_info->id = make_proc(0, &cur_info);
	if (cur_info->id == -1)
		while (!wait_all_proc(cur_info))
			;
	else
		proc_line(cur_info);
}
