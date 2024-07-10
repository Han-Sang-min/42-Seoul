/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PutMemInBuf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:24:53 by hansangmin        #+#    #+#             */
/*   Updated: 2022/07/28 20:38:29 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	buf_mem(size_t nbr, char *buf)
{
	if (nbr < 16)
	{
		*buf = "0123456789abcdef"[nbr & 15];
		return ;
	}
	buf_mem(nbr >> 4, buf - 1);
	*buf = "0123456789abcdef"[nbr & 15];
}

int	find_mem_len(size_t nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		nbr = nbr >> 4;
		len++;
	}
	return (len);
}

int	my_putmem(size_t nbr, t_flag_set *tfs)
{
	int		len;
	int		ret;

	len = find_mem_len(nbr);
	ret = len + 2;
	if (ret < tfs->width)
		ret = tfs->width;
	tfs->buf = (char *)malloc(ret + 1);
	if (!tfs->buf)
		return (-1);
	if (tfs->flag_minus)
		len += 2;
	init_buf(tfs, ret);
	if (tfs->flag_minus)
	{
		ft_memcpy(tfs->buf, "0x", 2);
		buf_mem(nbr, tfs->buf + len - 1);
	}
	else
	{
		ft_memcpy(tfs->buf + ret - len - 2, "0x", 2);
		buf_mem(nbr, tfs->buf + ret - 1);
	}
	return (ret);
}
