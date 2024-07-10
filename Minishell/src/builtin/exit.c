/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 02:03:25 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 10:26:35 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_exit(t_info *cur_info)
{
	int	i;

	i = 0;
	if (cur_info->stat.pid < 0)
		write(STDERR_FILENO, "exit\n", 5);
	if (cur_info->av[1] == NULL)
		exit(g_var.exit_code);
	while (cur_info->av[1][i])
	{
		if (!ft_isdigit(cur_info->av[1][i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cur_info->av[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		i++;
	}
	if (cur_info->av[2] != NULL)
	{
		cur_info->stat.stat = 256;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	else
		exit(ft_atoi(cur_info->av[1]));
	if (cur_info->stat.pid < 0)
		return (0);
	exit(0);
}
