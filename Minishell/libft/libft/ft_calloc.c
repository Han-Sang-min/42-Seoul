/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:21:30 by sangmhan          #+#    #+#             */
/*   Updated: 2022/07/20 13:28:11 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ret;

	ret = malloc(nmemb * size);
	if (!ret)
		return (NULL);
	ft_memset(ret, 0, nmemb * size);
	return (ret);
}
