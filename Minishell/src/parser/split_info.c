/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:45:20 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/19 01:45:21 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_quote_flag(char c, char *flag)
{
	if (c == '\'' || c == '"')
	{
		if (*flag == 0)
			*flag = c;
		else if (c == '\'' && *flag == '\'')
			*flag = 0;
		else if (c == '"' && *flag == '"')
			*flag = 0 ;
	}
	return ;
}

static int	get_word_count(char *str)
{
	int			i;
	char		flag;
	int			count;
	const char	*set = " \t\r\f\v";

	flag = 0;
	i = -1;
	count = 0;
	while (str[++i])
	{
		change_quote_flag(str[i], &flag);
		if (flag == 0 && str[i + 1] == '\0')
			count++;
		else if (flag == 0 && !(ft_strchr(set, str[i])) \
		&& ft_strchr(set, str[i + 1]))
		{
			count++;
			i++;
		}
	}
	return (count);
}

static int	get_word_len(int start, char*str)
{
	char		flag;
	int			len;
	const char	*set = " \t\r\f\v";

	flag = 0;
	len = 0;
	while (str[start + len])
	{
		change_quote_flag(str[start + len], &flag);
		if (flag == 0 && ft_strchr(set, str[start + len]))
			return (len);
		len++;
	}
	return (len);
}

static int	get_start(int start, char *str)
{
	const char	*set = " \t\r\f\v";

	while (str[start] && (ft_strchr(set, str[start])))
		start++;
	return (start);
}

char	**ft_split_info(char *str)
{
	int		i;
	int		start;
	int		wd_len;
	int		wd_cnt;
	char	**command_array;

	wd_cnt = get_word_count(str);
	command_array = (char **)malloc(sizeof(char *) * (wd_cnt + 1));
	if (!command_array)
		malloc_error();
	i = -1;
	start = get_start(0, str);
	while (++i < wd_cnt)
	{
		wd_len = get_word_len(start, str);
		command_array[i] = (char *)malloc(sizeof(char) * (wd_len +1));
		if (!command_array[i])
			malloc_error();
		ft_strlcpy(command_array[i], str + start, wd_len + 1);
		start = get_start(start + wd_len, str);
	}
	command_array[i] = NULL;
	return (command_array);
}
