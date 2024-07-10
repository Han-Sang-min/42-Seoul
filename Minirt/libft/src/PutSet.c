/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PutSet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 09:39:41 by hansangmin        #+#    #+#             */
/*   Updated: 2022/07/28 20:30:27 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	put_base(t_info_set *tis, t_flag_set *tfs)
{
	if (tfs->flag_minus)
	{
		ft_memset(tfs->buf, '0', tfs->flag_dot_nu);
		if (tis->len < tfs->flag_dot_nu)
			buf_nbr(tis->nbr, tis->base_len, tis->base, \
			tfs->buf + tfs->flag_dot_nu - 1);
		else
			buf_nbr(tis->nbr, tis->base_len, tis->base, \
			tfs->buf + tis->len - 1);
	}
	else
	{
		ft_memset(tfs->buf + tis->ret - tfs->flag_dot_nu, \
		'0', tfs->flag_dot_nu);
		buf_nbr(tis->nbr, tis->base_len, tis->base, tfs->buf + tis->ret - 1);
	}
	return (tis->ret);
}

int	mid_base(t_info_set *tis, t_flag_set *tfs)
{
	if (tis->ret < tfs->width)
		tis->ret = tfs->width;
	tfs->buf = (char *)malloc(tis->ret + 1);
	if (!tfs->buf)
		return (-1);
	init_buf(tfs, tis->ret);
	return (0);
}

int	cnt_base(long long nbr, int base)
{
	int	ret;

	ret = 1;
	if (nbr < 0)
		nbr *= -1;
	while (nbr >= base)
	{
		nbr /= base;
		ret++;
	}
	return (ret);
}
