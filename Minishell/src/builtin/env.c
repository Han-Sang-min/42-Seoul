/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:52:39 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/19 02:02:34 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_env(t_info *cur_info)
{
	int	idx;

	idx = 0;
	while ((*g_var.environ)[idx])
		printf("%s\n", (*g_var.environ)[idx++]);
	if (cur_info->stat.pid < 0)
		return (0);
	exit(0);
}
