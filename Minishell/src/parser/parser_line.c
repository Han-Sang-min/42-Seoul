/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:45:32 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/19 01:45:33 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_path_flag(t_info *info)
{
	t_info	*curr;

	curr = info;
	if (!curr->cmd)
		return ;
	while (curr)
	{
		if (!curr->cmd)
			return ;
		if (ft_strchr(curr->cmd, '/'))
			curr->path = 1;
		curr = curr->next;
	}
}

static void	malloc_info_argv(char **commands, t_info **head)
{
	int		i;
	t_info	*curr;

	i = -1;
	curr = *head;
	while (commands[++i] && curr)
	{
		if (commands[i][0] == PIPE_TYPE)
			curr = curr->next;
		else
			curr->ac++;
	}
	curr = *head;
	while (curr)
	{
		curr->av = (char **)malloc(sizeof(char *) * (curr->ac + 1));
		if (!curr->av)
			return (malloc_error());
		i = -1;
		while (++i <= curr->ac)
			curr->av[i] = NULL;
		curr = curr->next;
	}
}

void	init_info(char **commands, t_info **head)
{
	malloc_info_list(commands, head);
	malloc_info_argv(commands, head);
	init_info_list(commands, *head, -1, 0);
	set_path_flag(*head);
}

int	parser(char **input, t_info **info_head)
{
	char	**commands;
	char	**lexed;

	if (!check_input(*input))
		return (TRUE);
	*info_head = NULL;
	lexed = ft_split_info(*input);
	commands = parse_cmds(lexed);
	if (!check_syntax_errors(commands))
	{
		free_double_array(commands);
		return (TRUE);
	}
	init_info(commands, info_head);
	free_double_array(commands);
	return (FALSE);
}
