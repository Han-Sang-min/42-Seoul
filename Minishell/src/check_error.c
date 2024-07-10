/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:44:53 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 09:10:22 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	valid_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] <= 8 && str[i] >= 1)
			return (str[i]);
		i++;
	}
	return (9);
}

void	err_exit(char *cmd)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	exit(1);
}

int	check_syntax_errors(char **cmd)
{
	int	i;
	int	errno;

	i = 0;
	errno = 0;
	if (valid_str(cmd[0]) == PIPE_TYPE)
		errno++;
	while (cmd[i])
	{
		if ((valid_str(cmd[i]) >= 1 && valid_str(cmd[i]) <= 8) \
		&& (valid_str(cmd[i + 1]) >= 1 && valid_str(cmd[i + 1]) <= 8))
			errno++;
		i++;
	}
	if ((i > 0 && valid_str(cmd[i - 1]) < 9) && valid_str(cmd[i]) == -1)
		errno++;
	if (errno > 0)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", \
		STDERR_FILENO);
		g_var.exit_code = 258;
		return (0);
	}
	return (1);
}

void	malloc_error(void)
{
	ft_putendl_fd("minishell: fork: Cannot allocate memory", STDERR_FILENO);
	exit(1);
}

int	invalid_cmd_error(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("command not found", STDERR_FILENO);
	exit (127);
}
