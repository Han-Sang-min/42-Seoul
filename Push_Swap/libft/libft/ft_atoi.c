/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:31:59 by sangmhan          #+#    #+#             */
/*   Updated: 2022/11/13 01:09:42 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

long long	ft_atoi(const char *nptr)
{
	int			sign;
	long long	res;
	size_t		tmp;

	sign = 1;
	res = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign = -1;
	while (*nptr >= 48 && *nptr <= 57)
	{
		tmp = res * 10 + *nptr++ - 48;
		if (tmp > 9223372036854775807U && sign == 1)
			return (-1);
		if ((tmp > 9223372036854775808U && sign == -1))
			return (0);
		res = tmp;
	}
	return (sign * res);
}
