/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:44:37 by hansangmin        #+#    #+#             */
/*   Updated: 2022/11/22 00:57:31 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	common_part(char *av[], char *env[], int id, t_fds *fds)
{
	char	*cmd;

	close(fds->out[IN]);
	close(fds->out[OUT]);
	cmd = parsing_cmd(av, env, id);
	av = parsing_av(av, id);
	if (execve(cmd, av, env) == -1)
		cmd_err();
}

void	execute_first_cmd(char *av[], char *env[], int id, t_fds *fds)
{
	int		fd;

	fd = open(av[1], O_RDONLY, DEFFILEMODE);
	if (fd == -1)
		err_exit();
	dup2(fds->out[OUT], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	common_part(av, env, id, fds);
}

void	execute_middle_cmd(char *av[], char *env[], int id, t_fds *fds)
{
	dup2(fds->in[IN], STDIN_FILENO);
	dup2(fds->out[OUT], STDOUT_FILENO);
	close(fds->in[IN]);
	common_part(av, env, id, fds);
}

void	execute_last_cmd(char *av[], char *env[], int id, t_fds *fds)
{
	int		fd;

	fd = open(av[id + 3], O_WRONLY | O_CREAT | fds->doc, DEFFILEMODE);
	if (fd == -1)
		err_exit();
	dup2(fds->in[IN], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fds->in[IN]);
	close(fd);
	common_part(av, env, id, fds);
}
