/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:49:44 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/19 15:56:58 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exit_return(t_info *cur_info, int n)
{
	if (!n)
		printf("\n");
	if (cur_info->stat.pid < 0)
		return (0);
	exit (0);
}

static void	print_echo_args(t_info *cur_info, int idx)
{	
	while (cur_info->av[idx])
	{
		if (cur_info->av[idx + 1] == 0)
			printf("%s", cur_info->av[idx]);
		else
			printf("%s ", cur_info->av[idx]);
		idx++;
	}
}

int	builtin_echo(t_info *cur_info)
{
	char	*option;
	int		idx;
	int		n;

	n = FALSE;
	idx = 0;
	option = cur_info->av[++idx];
	if (option == NULL)
		return (exit_return(cur_info, n));
	if (*option == '-')
	{
		while (option && *++option == 'n')
			n = TRUE;
		if (*option != 0)
			n = FALSE;
	}
	if (n)
		idx++;
	print_echo_args(cur_info, idx);
	return (exit_return(cur_info, n));
}
