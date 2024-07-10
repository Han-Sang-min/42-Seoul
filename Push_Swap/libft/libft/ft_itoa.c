/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmhan <sangmhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:41:01 by sangmhan          #+#    #+#             */
/*   Updated: 2022/07/17 14:31:31 by sangmhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	mal_size(int n)
{
	int	ret;

	ret = 1;
	if (n < 0)
		ret++;
	n /= 10;
	while (n)
	{
		n /= 10;
		ret++;
	}
	return (ret);
}

static char	*chg_type(char *ret, long long n, int len)
{
	if (n < 0)
	{
		ret[0] = '-';
		n *= -1;
	}
	ret[len--] = 0;
	ret[len--] = "0123456789"[n % 10];
	n /= 10;
	while (n)
	{
		ret[len--] = "0123456789"[n % 10];
		n /= 10;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		len;

	len = mal_size(n);
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	return (chg_type(ret, n, len));
}
