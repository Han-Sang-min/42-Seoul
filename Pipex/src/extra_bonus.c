/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:24:57 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/22 11:36:08 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	here_doc(char *av[], t_fds *fds)
{
	char		*tmp;
	int			status;
	const pid_t	pid = fork();

	if (pid == 0)
	{
		close(fds->out[IN]);
		while (1)
		{
			tmp = get_next_line(0);
			if (!ft_strncmp(tmp, av[2], ft_strlen(av[2])) && \
			!ft_strncmp(tmp, av[2], ft_strlen(tmp) - 1))
				exit(0) ;
			write(fds->out[OUT], tmp, ft_strlen(tmp));
			free(tmp);
		}
	}
	wait(&status);
	fds->in[IN] = fds->out[IN];
	fds->in[OUT] = fds->out[OUT];
	close(fds->in[OUT]);
	pipe(fds->out);
	fds->doc = O_APPEND;
}

void	err_exit(void)
{
	perror("");
	exit(1);
}

void	cmd_err(void)
{`
	write(STDERR_FILENO, "Command not found\n", 19);
	exit(127);
}

void	ac_err(void)
{
	write(STDERR_FILENO, "Not enough number of arguments\n", 31);
	exit(1);
}
