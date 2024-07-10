/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonbpark <wonbpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:27:52 by wonbpark          #+#    #+#             */
/*   Updated: 2023/01/19 22:27:56 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int		index;
	size_t	i;

	index = ft_strlen(s1);
	i = 0;
	while (i < ft_strlen((char *)s2))
	{
		s1[index] = s2[i];
		i++;
		index++;
	}
	s1[index] = '\0';
	return (s1);
}
