/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:04:33 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 10:54:03 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_var g_var;

static char	*read_input(void)
{
	char	*read;
	char	cwd[PATH_MAX + 1];

	getcwd(cwd, PATH_MAX + 1);
	ft_strcat(cwd, " : \033[0m");
	printf("\033[1;32m");
	read = readline(cwd);
	if (read && *read)
		add_history(read);
	return (read);
}

static void	builtin_in_main(t_info *info)
{
	int	fds[2];

	init_child_signal_handler();
	fds[IN] = dup(STDIN_FILENO);
	fds[OUT] = dup(STDOUT_FILENO);
	info->fds[OUT][OUT] = dup(STDOUT_FILENO);
	info->fds[IN][IN] = dup(STDIN_FILENO);
	if (fds[IN] == -1 || fds[OUT] == -1 || \
	info->fds[OUT][OUT] == -1 || info->fds[IN][IN] == -1)
	{
		ft_putstr_fd("minishell : dup error occur\n", 2);
		return ;
	}
	if (set_redir(info))
		return ;
	builtin_check(info);
	if (dup2(fds[OUT], STDOUT_FILENO) == -1 || dup2(fds[IN], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("minishell : dup2 error occur\n", 2);
		exit (1);
	}
	close(fds[OUT]);
	close(fds[IN]);
}

void	exit_shell(char *line)
{
	free(line);
	ft_putstr_fd("exit\n", 2);
	exit(g_var.exit_code);
}

static void	shell_main(void)
{
	char	*line;
	t_info	*info;

	while (TRUE)
	{
		init_signal_handler();
		line = read_input();
		if (!line)
			exit_shell(line);
		if (parser(&line, &info) == FALSE)
		{
			g_var.exit_code = 0;
			if (info->pipe == FALSE && is_builtin(info))
				builtin_in_main(info);
			else
				exec_cmd(info);
			if (g_var.exit_code < 128)
				g_var.exit_code = last_info_code(info);
			delete_info_list(&info);
		}
		free(line);
	}
}

int	main(void)
{
	extern char		**environ;
	struct termios	org_term;

	g_var.environ = &environ;
	init_environ();
	tcgetattr(STDIN_FILENO, &org_term);
	shlvl_oldpwd();
	shell_main();
	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
}
