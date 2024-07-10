/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:32:42 by hansangmin        #+#    #+#             */
/*   Updated: 2023/01/19 22:33:16 by wonbpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	if (str1 == NULL || str2 == NULL)
		return (1);
	while (str1[i] && str2[i])
	{
		if (str1[i] < str2[i])
			return (-1);
		else if (str1[i] > str2[i])
			return (1);
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return (0);
	else if (str1[i] == '\0')
		return (-1);
	return (1);
}
