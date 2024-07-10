/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 02:33:41 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/19 16:20:15 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	env_gener(t_export key_value, int i, int key_len, int value_len)
{
	char	*env_string;
	char	**tmp;
	int		env_cnt;
	char	**free_tmp;

	env_cnt = 0;
	while ((*g_var.environ)[env_cnt])
		env_cnt++;
	tmp = (char **)malloc(sizeof(char *) * (env_cnt + 2));
	if (!tmp)
		malloc_error();
	ft_memmove(tmp, *g_var.environ, sizeof(char *) * (env_cnt));
	env_string = (char *)malloc(key_len + value_len + 2);
	ft_strlcpy(env_string, key_value.key, key_len + 1);
	ft_strlcat(env_string, "=", key_len + 2);
	ft_strlcat(env_string, key_value.value, key_len + value_len + 2);
	(tmp)[i] = env_string;
	(tmp)[i + 1] = NULL;
	free_tmp = *g_var.environ;
	*g_var.environ = tmp;
	free(free_tmp);
}

static void	add_env(t_export key_value)
{
	int			i;
	const int	key_len = ft_strlen(key_value.key);
	const int	value_len = ft_strlen(key_value.value);
	char		*env_string;

	i = -1;
	while ((*g_var.environ)[++i] != NULL)
		if ((!ft_strncmp((*g_var.environ)[i], key_value.key, \
		extra_len((*g_var.environ)[i]))) && (!ft_strncmp(key_value.key, \
		(*g_var.environ)[i], extra_len((*g_var.environ)[i]))))
			break ;
	if ((*g_var.environ)[i] != NULL)
	{
		env_string = (char *)malloc(key_len + value_len + 2);
		if (!env_string)
			malloc_error();
		ft_strlcpy(env_string, key_value.key, key_len + 1);
		ft_strlcat(env_string, "=", key_len + 2);
		ft_strlcat(env_string, key_value.value, key_len + value_len + 2);
		free((*g_var.environ)[i]);
		(*g_var.environ)[i] = env_string;
	}
	else
		env_gener(key_value, i, \
		ft_strlen(key_value.key), ft_strlen(key_value.value));
}

static t_export	*add_exp(t_export key_value, t_export *export_env)
{
	t_export	*st;

	st = export_env;
	while (export_env && ft_strcmp(export_env->key, key_value.key))
		export_env = export_env->next;
	if (export_env != NULL)
	{
		if (key_value.value != NULL)
			if (export_env->value != NULL)
				free(export_env->value);
		export_env->value = key_value.value;
		free(key_value.key);
		export_env = st;
	}
	else
	{
		export_env = (t_export *)malloc(sizeof(t_export));
		if (!export_env)
			malloc_error();
		export_env->key = key_value.key;
		export_env->value = key_value.value;
		export_env->next = st;
	}
	return (export_env);
}

static void	pnt_export(t_export *export_env)
{
	if (export_env == NULL)
		return ;
	pnt_export(export_env->next);
	if (export_env->value == NULL)
		printf("declare -x %s\n", export_env->key);
	else
		printf("declare -x %s=\"%s\"\n", export_env->key, export_env->value);
}

int	builtin_export(t_info *cur_info, t_export **export_env)
{
	t_export	key_value;
	int			idx;

	idx = 0;
	if (cur_info->av[++idx] == NULL)
		pnt_export(*export_env);
	else
	{
		while (cur_info->av[idx])
		{
			key_value = split_key_value(cur_info->av[idx]);
			if (key_value.value != NULL)
				add_env(key_value);
			*export_env = add_exp(key_value, *export_env);
			idx++;
		}
	}
	if (cur_info->stat.pid < 0)
		return (0);
	exit(0);
}
