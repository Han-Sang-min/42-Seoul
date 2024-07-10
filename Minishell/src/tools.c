/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:19:05 by hansangmin        #+#    #+#             */
/*   Updated: 2023/01/21 10:41:07 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_export	split_key_value(char *line)
{
	t_export	key_value;
	const char	*point = ft_strchr(line, '=');

	key_value.value = NULL;
	key_value.next = NULL;
	if (point == NULL)
	{
		key_value.key = ft_substr(line, 0, ft_strlen(line));
		return (key_value);
	}
	key_value.key = ft_substr(line, 0, obs_strlen(line, '='));
	line = (char *)point + 1;
	key_value.value = ft_substr(line, 0, ft_strlen(line));
	return (key_value);
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
		err_exit("close error");
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		err_exit("dup2 error");
}

void	ft_pipe(int fds[2])
{
	ft_close(fds[OUT]);
	if (pipe(fds) == -1)
		err_exit("pipe error");
}

int	obs_strlen(char *str, char lmt)
{
	int	len;

	len = 0;
	while (str[len] != lmt && str[len])
		len++;
	return (len);
}
