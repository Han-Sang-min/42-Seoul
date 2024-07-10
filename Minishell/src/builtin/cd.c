/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:51:04 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 10:20:21 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	renew_pwd(void)
{
	char	cwd[PATH_MAX + 1];
	t_info	*info;
	char	*line;

	getcwd(cwd, PATH_MAX + 1);
	line = ft_strjoin("export PWD=", cwd);
	parser(&line, &info);
	builtin_check(info);
	free(line);
	delete_info_list(&info);
}

int	builtin_cd(t_info *cur_info)
{
	int	err_check;

	err_check = chdir(cur_info->av[1]);
	if (err_check)
	{
		cur_info->stat.stat = 256;
		perror("Arguments error");
		if (cur_info->stat.pid < 0)
			return (0);
		exit(1);
	}
	renew_pwd();
	if (cur_info->stat.pid < 0)
		return (0);
	exit(0);
}
