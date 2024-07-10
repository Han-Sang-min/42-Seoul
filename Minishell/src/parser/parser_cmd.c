/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:45:25 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/19 01:45:26 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_symbol_type(char **temp, int cnt, char symbol)
{
	if (cnt == 1 && symbol == '|')
		ft_strjoin_char(temp, PIPE_TYPE);
	else if (cnt == 1 && symbol == '<')
		ft_strjoin_char(temp, REDIR_I);
	else if (cnt == 1 && symbol == '>')
		ft_strjoin_char(temp, REDIR_O);
	else if (cnt == 2 && symbol == '<')
		ft_strjoin_char(temp, HEREDOC);
	else if (cnt == 2 && symbol == '>')
		ft_strjoin_char(temp, REDIR_APPEND);
	else
		ft_strjoin_char(temp, DFL);
	return ;
}

static int	is_separator(char **temp, char *cmd, int *i)
{
	char	symbol;
	int		cnt;

	cnt = 0;
	if (cmd[*i] == '|' || cmd[*i] == '>' || cmd[*i] == '<')
		symbol = cmd[*i];
	else
		return (0);
	ft_strjoin_char(temp, SEPAR);
	while (cmd[(*i)] == symbol)
	{
		cnt++;
		(*i)++;
	}
	(*i)--;
	handle_symbol_type(temp, cnt, symbol);
	return (1);
}

static void	parse_command(char **temp, char *command)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (command[++i])
	{
		if (quote != '\'' && command[i] == '$')
			i = expand_env(temp, command, i);
		else if (!quote && command[i] == '~' && ft_strlen(command) == 1)
			expand_home(temp, "HOME", &i);
		if (!quote && (command[i] == '\'' || command[i] == '"'))
			change_quote_flag(command[i], &quote);
		else if (quote && command[i] == quote)
			change_quote_flag(command[i], & quote);
		else if (!quote && is_separator(temp, command, &i))
			ft_strjoin_char(temp, SEPAR);
		else
			ft_strjoin_char(temp, command[i]);
	}
	ft_strjoin_char(temp, SEPAR);
}

char	**parse_cmds(char **commands)
{
	int		i;
	char	*temp;
	char	**result;

	i = -1;
	temp = ft_strdup("");
	while (commands[++i])
		parse_command(&temp, commands[i]);
	free_double_array(commands);
	result = ft_split(temp, SEPAR);
	free(temp);
	temp = NULL;
	return (result);
}
