/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:55:06 by sangmhan          #+#    #+#             */
/*   Updated: 2023/01/21 08:47:01 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	ret = (char *)malloc(len);
	if (!ret)
		exit (1);
	ft_memcpy(ret, s, len);
	return (ret);
}
