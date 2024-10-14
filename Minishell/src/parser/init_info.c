/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:45:17 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/19 11:07:19 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_redir(t_info *curr, int type, char *file_name, int *i)
{
	if (file_name != NULL)
		(*i)++;
	if (type == REDIR_O)
	{
		curr->redir[OUT].type = REDIR_O;
		if (curr->redir[OUT].file_name)
			free(curr->redir[OUT].file_name);
		curr->redir[OUT].file_name = file_name;
	}
	else if (type == REDIR_APPEND)
	{
		curr->redir[OUT].type = REDIR_APPEND;
		if (curr->redir[OUT].file_name)
			free(curr->redir[OUT].file_name);		
		curr->redir[OUT].file_name = file_name;
	}
	else if (type == REDIR_I)
	{
		curr->redir[IN].type = REDIR_I;
		if (curr->redir[IN].file_name)
			free(curr->redir[IN].file_name);
		curr->redir[IN].file_name = file_name;
	}
	if (type == HEREDOC)
	{
		curr->redir[IN].type = HEREDOC;
		if (curr->redir[IN].file_name)
			free(curr->redir[IN].file_name);
		curr->redir[IN].file_name = file_name;
	}
	return (1);
}

int	check_redir(t_info *curr, char **commands, int *i)
{
	int		j;

	j = *i;
	if (commands[j + 1] != NULL)
	{
		if (commands[*i][0] == HEREDOC)
			return (init_redir(curr, HEREDOC, ft_strdup(commands[*i + 1]), i));
		else if (commands[*i][0] == REDIR_I)
			return (init_redir(curr, REDIR_I, ft_strdup(commands[*i + 1]), i));
		else if (commands[*i][0] == REDIR_APPEND)
			return (init_redir(curr, REDIR_APPEND, ft_strdup(commands[*i + 1]), i));
		else if (commands[*i][0] == REDIR_O)
			return (init_redir(curr, REDIR_O, ft_strdup(commands[*i + 1]), i));
	}
	return (0);
}

// static void	set_new_output_file(int	*index, t_info *curr)
// {
// 	curr->av[(*index)++] = ft_strdup("touch");
// 	curr->av[(*index)++] = ft_strdup(curr->redir[OUT].file_name);
// 	curr->cmd = curr->av[0];
// 	return ;
// }

static void	sub_init_pipes(t_info *curr)
{
	curr->pipe = 1;
	curr->fds[0][0] = 0;
	curr->fds[0][1] = 0;
	curr->fds[1][0] = 0;
	curr->fds[1][1] = 0;
}

void	init_info_list(char **commands, t_info *curr, int i, int index)
{
	while (commands[++i] && curr)
	{
		if (commands[i][0] == PIPE_TYPE)
		{
			sub_init_pipes(curr);
			curr = curr->next;
			index = 0;
		}
		else if (check_redir(curr, commands, &i))
		{
			if (i == 0)
				return ;
			/* if ((commands[i - 1][0] == REDIR_O || \
			commands[i - 1][0] == REDIR_APPEND) \
			&& (curr->redir[OUT].file_name && curr->cmd == NULL))
			 	set_new_output_file(&index, curr); */
		}
		else
		{
			curr->av[index++] = ft_strdup(commands[i]);
			curr->cmd = curr->av[0];
		}
	}	
}
