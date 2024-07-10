/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:12:37 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 10:30:51 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	shlvl_oldpwd(void)
{
	t_info	*info;
	char	*line;
	char	*tmp;
	int		lvl;

	line = getenv("SHLVL");
	if (!line)
		line = ft_strdup("");
	lvl = ft_atoi(line) + 1;
	tmp = ft_itoa(lvl);
	line = ft_strjoin("export SHLVL=", tmp);
	free(tmp);
	parser(&line, &info);
	builtin_check(info);
	delete_info_list(&info);
	free(line);
	line = ft_strdup("unset OLDPWD");
	parser(&line, &info);
	builtin_check(info);
	delete_info_list(&info);
	free(line);
}

void	init_environ(void)
{
	char	*tmp;
	int		idx;

	idx = 0;
	while ((*g_var.environ)[idx])
	{
		tmp = (*g_var.environ)[idx];
		(*g_var.environ)[idx] = ft_strdup(tmp);
		idx++;
	}
}
