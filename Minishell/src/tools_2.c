/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:45:12 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 10:15:55 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_double_array(char **arr)
{
	int		i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
	return ;
}

void	ft_strjoin_char(char **dst, char ch)
{
	char	str[2];
	char	*temp;

	temp = *dst;
	str[0] = ch;
	str[1] = '\0';
	*dst = ft_strjoin(*dst, str);
	free(temp);
	temp = NULL;
}

int	extra_len(char *str)
{
	int	ret;

	ret = 0;
	while (str[ret] != '=' && str[ret])
		ret++;
	return (ret);
}

int	last_info_code(t_info *info)
{
	while (info->next)
		info = info->next;
	return (((*(int *)&(info->stat.stat)) >> 8) & 0x000000ff);
}
