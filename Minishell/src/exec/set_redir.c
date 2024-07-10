/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:38:57 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 10:46:30 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	extra_redir_in(t_info *cur_info)
{
	char	*tmp;

	cur_info->fds[IN][IN] = open("/tmp/tmp_here_doc", \
	O_WRONLY | O_TRUNC | O_CREAT, DEFFILEMODE);
	if (!cur_info->fds[IN][IN])
		return (err_here_doc(cur_info));
	init_heredoc_signal_handler();
	while (TRUE)
	{
		tmp = readline("> ");
		if (!ft_strcmp(tmp, cur_info->redir[IN].file_name))
		{
			free(tmp);
			break ;
		}
		write(cur_info->fds[IN][IN], tmp, ft_strlen(tmp));
		write(cur_info->fds[IN][IN], "\n", 1);
		free(tmp);
	}
	close(cur_info->fds[IN][IN]);
	cur_info->fds[IN][IN] = open("/tmp/tmp_here_doc", O_RDONLY);
	init_child_signal_handler();
	return (0);
}

static int	redir_in(t_info *cur_info)
{
	ft_close(cur_info->fds[IN][IN]);
	if (cur_info->redir[IN].type == REDIR_I)
	{
		cur_info->fds[IN][IN] = \
		open(cur_info->redir[IN].file_name, O_RDONLY);
		if (cur_info->fds[IN][IN] == -1)
			return (err_redir_in(cur_info));
	}
	else
		if (extra_redir_in(cur_info))
			return (1);
	return (0);
}

static int	redir_out(t_info *cur_info)
{
	ft_close(cur_info->fds[OUT][OUT]);
	if (cur_info->redir[OUT].type == REDIR_O)
		cur_info->fds[OUT][OUT] = \
		open(cur_info->redir[OUT].file_name, \
		O_WRONLY | O_TRUNC | O_CREAT, DEFFILEMODE);
	else
		cur_info->fds[OUT][OUT] = \
		open(cur_info->redir[OUT].file_name, \
		O_WRONLY | O_APPEND | O_CREAT, DEFFILEMODE);
	if (cur_info->fds[OUT][OUT] == -1)
		return (err_redir_out(cur_info));
	return (0);
}

int	set_redir(t_info *cur_info)
{
	if (cur_info->redir[IN].type == REDIR_I \
	|| cur_info->redir[IN].type == HEREDOC)
		if (redir_in(cur_info))
			return (1);
	ft_dup2(cur_info->fds[IN][IN], STDIN_FILENO);
	ft_close(cur_info->fds[IN][IN]);
	if (cur_info->redir[OUT].type == REDIR_O \
	|| cur_info->redir[OUT].type == REDIR_APPEND)
		if (redir_out(cur_info))
			return (1);
	ft_dup2(cur_info->fds[OUT][OUT], STDOUT_FILENO);
	ft_close(cur_info->fds[OUT][OUT]);
	return (0);
}
