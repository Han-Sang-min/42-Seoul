/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 02:09:22 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 10:27:27 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_export	*extra_unset_del_one(t_export *target)
{
	t_export	*ret;

	ret = target->next;
	free(target->key);
	if (target->value != NULL)
		free(target->value);
	free(target);
	return (ret);
}

static void	extra_unset_del(t_export *prev, t_export *target)
{
	free(target->key);
	if (target->value != NULL)
		free(target->value);
	prev->next = target->next;
	free(target);
}

static int	extra_unset_cnt(int env_idx)
{
	int	ret;

	ret = 0;
	while ((*g_var.environ)[env_idx])
	{
		ret++;
		env_idx++;
	}
	return (ret);
}

static void	unset_env(t_info *cur_info, t_export **export_env, int av_idx)
{
	t_export	*tmp;

	tmp = *export_env;
	if (!ft_strcmp(tmp->key, cur_info->av[av_idx]))
			*export_env = extra_unset_del_one(tmp);
	else
	{
		while (tmp)
		{
			if (tmp->next && !ft_strcmp(tmp->next->key, \
			cur_info->av[av_idx]))
			{
				extra_unset_del(tmp, tmp->next);
				break ;
			}
			tmp = tmp->next;
		}
	}
}

int	builtin_unset(t_info *cur_info, t_export **export_env, \
size_t av_idx, size_t key_len)
{
	int			env_idx;

	av_idx = 0;
	while (cur_info->av[++av_idx])
	{
		env_idx = -1;
		key_len = ft_strlen(cur_info->av[av_idx]);
		while ((*g_var.environ)[++env_idx])
		{
			if (ft_strncmp((*g_var.environ)[env_idx], cur_info->av[av_idx], \
			key_len) == 0 && (*g_var.environ)[env_idx][key_len] == '=')
			{
				free((*g_var.environ)[env_idx]);
				ft_memmove(&(*g_var.environ)[env_idx], \
				&(*g_var.environ)[env_idx + 1], \
				extra_unset_cnt(env_idx) * sizeof(char *));
				break ;
			}
		}
		unset_env(cur_info, export_env, av_idx);
	}
	if (cur_info->stat.pid < 0)
		return (0);
	exit(0);
}
