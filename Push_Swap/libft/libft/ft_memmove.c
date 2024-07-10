/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:07:13 by sangmhan          #+#    #+#             */
/*   Updated: 2022/07/20 14:25:53 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			idx;
	unsigned char	*t_dst;
	unsigned char	*t_src;

	idx = -1;
	t_dst = (unsigned char *)dst;
	t_src = (unsigned char *)src;
	if (dst == src)
		return (dst);
	if (dst < src)
		while (++idx < len)
			t_dst[idx] = t_src[idx];
	else
		while (++idx < len)
			t_dst[len - idx - 1] = t_src[len - idx - 1];
	return (dst);
}
