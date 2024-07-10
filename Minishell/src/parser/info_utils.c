/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:45:14 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/19 01:45:15 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_pipes(char **commands)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (commands[i])
	{
		if (commands[i][0] == PIPE_TYPE)
			count++;
		i++;
	}
	return (count);
}

t_info	*create_info_node(t_info *prev, int i)
{
	t_info	*node;

	node = (t_info *)malloc(sizeof(t_info));
	if (!node)
		malloc_error();
	node->id = i;
	node->pipe = 0;
	node->path = 0;
	node->fds[0][0] = 0;
	node->fds[0][1] = 0;
	node->fds[1][1] = 0;
	node->fds[1][1] = 0;
	node->cmd = NULL;
	node->av = NULL;
	node->ac = 0;
	node->redir[IN].type = -1;
	node->redir[IN].file_name = NULL;
	node->redir[OUT].type = -1;
	node->redir[OUT].file_name = NULL;
	node->stat.pid = -1;
	node->stat.stat = 0;
	node->next = NULL;
	node->prev = prev;
	return (node);
}

void	malloc_info_list(char **commands, t_info **head)
{
	t_info	*node;
	t_info	*prev;
	int		count;
	int		i;

	i = 0;
	prev = NULL;
	count = count_pipes(commands);
	while (count >= 0)
	{
		node = create_info_node(prev, i);
		if (!*head)
			*head = node;
		if (prev)
			prev->next = node;
		prev = node;
		count--;
		i++;
	}
}

void	delete_info_list(t_info **info)
{
	t_info	*temp;
	t_info	*to_delete;

	temp = *info;
	while (temp)
	{
		to_delete = temp;
		temp = temp->next;
		if (to_delete->redir[IN].file_name != NULL)
			free(to_delete->redir[IN].file_name);
		if (to_delete->redir[OUT].file_name != NULL)
			free(to_delete->redir[OUT].file_name);
		free_double_array(to_delete->av);
		free(to_delete);
		to_delete = NULL;
	}
	return ;
}
