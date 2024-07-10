/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:45:09 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/19 01:45:10 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quote_pairs(char *input)
{
	int		i;
	char	c;

	i = -1;
	c = 0;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (c == 0)
				c = input[i];
			else if (c == '\'' && input[i] == '\'')
				c = 0;
			else if (c == '"' && input[i] == '"')
				c = 0;
			else if (c == '\'' && input[i] == '"')
				continue ;
			else if (c == '"' && input[i] == '\'')
				continue ;
		}
	}
	return (c == 0);
}

int	check_input(char *input)
{
	int			i;
	int			whitespaces;
	const char	*set = " \t\r\f\v";

	i = -1;
	whitespaces = 0;
	if (!input)
		return (0);
	while (input[++i])
	{
		if (input[i] == ' ' || ft_strchr(set, input[i]))
			whitespaces++;
	}
	if (whitespaces == (int)ft_strlen(input))
	{
		add_history(input);
		return (0);
	}
	if (!check_quote_pairs(input))
	{
		ft_putendl_fd("minishell: error: invalid quotes", STDERR_FILENO);
		return (0);
	}
	return (1);
}
