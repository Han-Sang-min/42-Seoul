/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 07:37:26 by sangmiha          #+#    #+#             */
/*   Updated: 2022/07/24 07:37:55 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static void	free_all(char **res, int idx)
{
	while (idx--)
		free(res[idx]);
	free(res);
}

static int	mal_size(char const *s, char c)
{
	int	ret;

	ret = 0;
	while (*++s)
	{
		if (!is_sep(*s, c))
			ret++;
		while (!is_sep(*s, c) && *(s + 1))
			s++;
	}
	return (ret);
}

static char	*ptr_arr(char const *s, char c)
{
	int		len;
	char	*ret;

	len = 0;
	while (!is_sep(s[len], c) && s[len])
		len++;
	ret = ft_substr(s, 0, len);
	if (!ret)
		return (NULL);
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		idx;

	res = (char **)malloc(sizeof(char *) * (mal_size(s - 1, c) + 1));
	if (!res)
		return (NULL);
	s--;
	idx = 0;
	while (*++s)
	{
		if (!is_sep(*s, c))
		{
			res[idx] = ptr_arr(s, c);
			if (!res[idx++])
			{
				free_all(res, idx);
				return (NULL);
			}
		}
		while (!is_sep(*s, c) && *(s + 1))
			s++;
	}
	res[idx] = 0;
	return (res);
}
