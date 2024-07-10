/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmhan <sangmhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 02:16:54 by sangmiha          #+#    #+#             */
/*   Updated: 2022/07/17 14:33:17 by sangmhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	len;

	while (isinset(*s1, set))
		s1++;
	len = ft_strlen(s1);
	if (len == 0)
		return (ft_strdup(""));
	while (isinset(*(s1 + len - 1), set))
		len--;
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, len + 1);
	return (ret);
}
