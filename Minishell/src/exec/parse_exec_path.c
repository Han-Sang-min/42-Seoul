/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:04:07 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 10:15:16 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_path(char **path)
{
	*path = ft_strchr(*path, ':') + 1;
	if ((long long)*path > 1)
		return (1);
	return (0);
}

static char	*extra_parsing_cmd(char *cmd, \
char *path, char *ret_cmd, const int cmd_size)
{
	struct stat	sb;
	int	path_size;

	while (TRUE)
	{
		path_size = obs_strlen(path, ':');
		ret_cmd = ft_calloc(cmd_size + path_size + 2, sizeof(char));
		if (!ret_cmd)
			malloc_error();
		ft_strlcpy(ret_cmd, path, path_size + 1);
		ft_strlcat(ret_cmd, "/", path_size + 2);
		ft_strlcat(ret_cmd, cmd, cmd_size + path_size + 2);
		stat(ret_cmd, &sb);
		if ((!access(ret_cmd, F_OK | X_OK) || !find_path(&path)) \
		&& ((sb.st_mode & S_IFMT) != S_IFDIR))
			break ;
		free(ret_cmd);
	}
	return (ret_cmd);
}

char	*parsing_cmd(char *cmd)
{
	char		*ret_cmd;
	char		*path;
	struct stat	sb;
	const int	cmd_size = ft_strlen(cmd);

	stat(cmd, &sb);
	if (!access(cmd, F_OK | X_OK) && ((sb.st_mode & S_IFMT) == S_IFREG))
		return (cmd);
	ret_cmd = (char *)malloc(cmd_size + 2);
	if (!ret_cmd)
		malloc_error();
	ft_strlcpy(ret_cmd, "./", 3);
	ft_strlcat(ret_cmd, cmd, cmd_size + 3);
	stat(ret_cmd, &sb);
	if (!access(cmd, F_OK | X_OK) && ((sb.st_mode & S_IFMT) == S_IFREG))
	{
		free(cmd);
		return (ret_cmd);
	}
	free(ret_cmd);
	path = getenv("PATH");
	if (path == NULL)
		err_exit(cmd);
	ret_cmd = extra_parsing_cmd(cmd, path, ret_cmd, cmd_size);
	free(cmd);
	stat(ret_cmd, &sb);
	if (access(ret_cmd, F_OK | X_OK) || ((sb.st_mode & S_IFMT) != S_IFREG))
		invalid_cmd_error(cmd);
	return (ret_cmd);
}
