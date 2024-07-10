/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 07:49:46 by hansangmin        #+#    #+#             */
/*   Updated: 2023/01/21 08:58:35 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	err_redir_out(t_info *cur_info)
{
	ft_putstr_fd("redirection out write fail : ", 2);
	perror("");
	if (cur_info->stat.pid < 0)
		return (1);
	exit(1);
}

int	err_redir_in(t_info *cur_info)
{
	ft_putstr_fd("redirection in open fail : ", 2);
	perror("");
	if (cur_info->stat.pid < 0)
		return (1);
	exit(1);
}

int	err_here_doc(t_info *cur_info)
{
	ft_putstr_fd("히어독 경로 권한 확인 : ", 2);
	perror("");
	if (cur_info->stat.pid < 0)
		return (1);
	exit(1);
}