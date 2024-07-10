/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:14:06 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/22 01:10:47 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	find_path(char **path)
{
	if (!ft_strncmp(*path, "PATH=", 5))
	{
		*path += 5;
		return (1);
	}
	*path = ft_strchr(*path, ':') + 1;
	if ((long long)*path > 1)
		return (1);
	return (0);
}

int	pipex_strlen(char *str, char lmt)
{
	int	len;

	len = 0;
	while (str[len] != lmt && str[len])
		len++;
	return (len);
}

char	*parsing_cmd(char *av[], char *env[], int id)
{
	char	*cmd;
	char	*path;
	int		path_size;
	int		aloc_size;

	aloc_size = pipex_strlen(av[id + 2], ' ');
	while (!ft_strnstr(*env, "PATH=", 5))
		env++;
	path = *env;
	while (find_path(&path))
	{
		path_size = pipex_strlen(path, ':');
		cmd = ft_calloc(aloc_size + path_size + 2, sizeof(char));
		if (!cmd)
			err_exit();
		ft_strlcpy(cmd, path, path_size + 1);
		ft_strlcat(cmd, "/", path_size + 2);
		ft_strlcat(cmd, av[id + 2], aloc_size + path_size + 2);
		if (!access(cmd, F_OK))
			break ;
		free(cmd);
	}
	if (access(cmd, F_OK))
		cmd_err();
	return (cmd);
}

char	**parsing_av(char *av[], int id)
{
	char		**ret;
	int			aloc_size;
	int			idx;
	const char	*option = ft_strchr(av[id + 2], ' ');

	idx = 0;
	ret = ft_calloc(3, sizeof(char *));
	if (!ret)
		err_exit();
	aloc_size = ft_strlen(av[0]) + 1;
	ret[idx] = ft_calloc(aloc_size, sizeof(char));
	if (!ret[idx])
		err_exit();
	ft_strlcpy(ret[idx++], av[0], aloc_size);
	if (option)
	{
		ret[idx] = ft_calloc(ft_strlen(option), sizeof(char));
		if (!ret[idx])
			err_exit();
		ft_strlcpy(ret[idx++], option + 1, ft_strlen(option));
	}
	return (ret);
}
