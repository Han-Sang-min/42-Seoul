/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmhan <sangmhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:53:25 by sangmiha          #+#    #+#             */
/*   Updated: 2022/07/17 12:13:01 by sangmhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	ret;
	size_t	len;

	ret = ft_strlen(src);
	if (dstsize)
	{
		if (ret < dstsize)
			len = ret;
		else
			len = dstsize - 1;
		ft_memcpy(dst, src, len);
		dst[len] = 0;
	}
	return (ret);
}
