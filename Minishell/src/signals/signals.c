/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:45:02 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/19 17:08:24 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sig_handle_proc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_var.exit_code = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		g_var.exit_code = 131;
	}
}

void	sig_handle_sigint(int sig)
{	
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("\0", 0);
		rl_on_new_line();
		printf("\b\033[1;32m");
		rl_redisplay();
		printf("\033[0m");
		g_var.exit_code = 1;
	}
	if (sig == SIGQUIT)
		return ;
}

void	init_heredoc_signal_handler(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	init_child_signal_handler(void)
{
	signal(SIGINT, sig_handle_proc);
	signal(SIGQUIT, sig_handle_proc);
}

void	init_signal_handler(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
	signal(SIGINT, sig_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
