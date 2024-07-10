/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 01:34:22 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 08:47:21 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	ret = malloc(len + 1);
	if (!ret)
		exit (1);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}
