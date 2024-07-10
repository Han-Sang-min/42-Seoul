/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 16:18:38 by sangmhan          #+#    #+#             */
/*   Updated: 2022/07/20 13:29:44 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		idx;
	char	*ret;

	idx = -1;
	ret = (char *)malloc(ft_strlen(s) + 1);
	if (!ret)
		return (NULL);
	while (s[++idx])
		ret[idx] = f(idx, s[idx]);
	ret[idx] = 0;
	return (ret);
}
