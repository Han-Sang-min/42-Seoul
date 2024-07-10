/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:50:11 by sangmhan          #+#    #+#             */
/*   Updated: 2022/07/13 01:31:57 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	tmp;

	if (!*little)
		return ((char *)big);
	while (*big && len--)
	{
		tmp = 0;
		if (*big == *little)
			while (*(little + tmp) && *(big + tmp) == *(little + tmp) \
			&& tmp <= len)
				tmp++;
		if (!*(little + tmp))
			return ((char *)big);
		big++;
	}
	return (0);
}
