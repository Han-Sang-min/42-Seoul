/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:59:18 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 10:24:11 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_export	*init_export(void)
{
	t_export		*export_env;
	t_export		*new_export;
	t_export		key_value;
	int				idx;

	idx = -1;
	export_env = NULL;
	while ((*g_var.environ)[++idx])
	{
		new_export = (t_export *)malloc(sizeof(t_export));
		if (!new_export)
			malloc_error();
		key_value = split_key_value((*g_var.environ)[idx]);
		new_export->key = key_value.key;
		new_export->value = key_value.value;
		new_export->next = NULL;
		if (export_env == NULL)
			export_env = new_export;
		else
		{
			new_export->next = export_env;
			export_env = new_export;
		}
	}
	return (export_env);
}

int	is_builtin(t_info *cur_info)
{
	if (!ft_strcmp(cur_info->cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cur_info->cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cur_info->cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cur_info->cmd, "export"))
		return (1);
	else if (!ft_strcmp(cur_info->cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cur_info->cmd, "env"))
		return (1);
	else if (!ft_strcmp(cur_info->cmd, "exit"))
		return (1);
	else
		return (0);
}

int	builtin_check(t_info *cur_info)
{
	static t_export	*export_env;
	int				ret_code;

	if (export_env == NULL)
		export_env = init_export();
	if (!ft_strcmp(cur_info->cmd, "echo"))
		ret_code = builtin_echo(cur_info);
	else if (!ft_strcmp(cur_info->cmd, "cd"))
		ret_code = builtin_cd(cur_info);
	else if (!ft_strcmp(cur_info->cmd, "pwd"))
		ret_code = builtin_pwd(cur_info);
	else if (!ft_strcmp(cur_info->cmd, "export"))
		ret_code = builtin_export(cur_info, &export_env);
	else if (!ft_strcmp(cur_info->cmd, "unset"))
		ret_code = builtin_unset(cur_info, &export_env, 0, 0);
	else if (!ft_strcmp(cur_info->cmd, "env"))
		ret_code = builtin_env(cur_info);
	else if (!ft_strcmp(cur_info->cmd, "exit"))
		ret_code = builtin_exit(cur_info);
	else
		return (-1);
	return (ret_code);
}
