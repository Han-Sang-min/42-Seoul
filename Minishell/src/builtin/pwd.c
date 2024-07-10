/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 02:07:17 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/19 02:07:44 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_pwd(t_info *cur_info)
{
	char	cwd[PATH_MAX + 1];

	getcwd(cwd, PATH_MAX + 1);
	printf("%s\n", cwd);
	if (cur_info->stat.pid < 0)
		return (0);
	exit(0);
}
