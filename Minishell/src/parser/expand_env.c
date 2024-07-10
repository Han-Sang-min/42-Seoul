/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:45:23 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/19 01:46:43 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_key(char *cmd, int start)
{
	int		i;
	int		len;
	char	*key;

	len = 0;
	if (cmd[start] == '$')
		start++;
	i = start;
	if (cmd[i] == '?')
		return (ft_strdup("?"));
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]))
			break ;
		i++;
		len++;
	}
	key = ft_substr(cmd, start, len);
	return (key);
}

void	expand_home(char **temp, char *key, int *i)
{
	char	*value;
	char	*aux;

	(*i)++;
	value = getenv(key);
	if (value == NULL)
		return ;
	aux = *temp;
	*temp = ft_strjoin(*temp, value);
	free(aux);
	return ;
}

int	expand_env(char **temp, char *cmd, int start)
{
	char	*key;
	char	*value;
	char	*aux;

	key = get_key(cmd, start);
	if (!ft_strncmp(key, "$", ft_strlen(key)))
		value = ft_strdup("$");
	else if (ft_strlen(key) == 0 && cmd[start + 1] != '"')
		value = ft_strdup(" ");
	else if (!ft_strncmp(key, "?", ft_strlen(key)))
		value = ft_itoa(g_var.exit_code);
	else
	{	
		value = ft_strdup(getenv(key));
		if (value == NULL)
			value = ft_strdup("");
	}
	aux = *temp;
	*temp = ft_strjoin(*temp, value);
	start += ft_strlen(key) + 1;
	free(value);
	free(key);
	free(aux);
	return (start);
}
