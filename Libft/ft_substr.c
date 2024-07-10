/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmhan <sangmhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 01:34:22 by sangmiha          #+#    #+#             */
/*   Updated: 2022/07/17 12:13:25 by sangmhan         ###   ########.fr       */
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
		return (ret);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}
