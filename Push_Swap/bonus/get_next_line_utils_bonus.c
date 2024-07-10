/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:40:04 by hansangmin        #+#    #+#             */
/*   Updated: 2022/11/15 20:53:37 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		sizetotal;
	char	*res;
	int		i;
	int		j;

	i = -1;
	sizetotal = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (sizetotal + 1));
	if (!res || !s1 || !s2)
		return (NULL);
	while (s1[++i] != 0)
		res[i] = s1[i];
	j = -1;
	while (s2[++j] != 0)
		res[i++] = s2[j];
	res[sizetotal] = 0;
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s) + 1;
	while (i < len)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}

void	*ft_memset(void *dest, int c, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
		((unsigned char *)dest)[i++] = (unsigned char)c;
	return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ret;

	ret = malloc(nmemb * size);
	if (!ret)
		return (NULL);
	ft_memset(ret, 0, nmemb * size);
	return (ret);
}

size_t	ft_strlen(const char *str)
{
	size_t	ret;

	ret = 0;
	while (str[ret])
		ret++;
	return (ret);
}
