/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PutUnsignedInBuf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:26:52 by hansangmin        #+#    #+#             */
/*   Updated: 2022/07/28 20:40:52 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	init_precision_0(t_info_set *tis, t_flag_set *tfs)
{
	tfs->flag_zero = ' ';
	if (tfs->flag_dot_nu < tfs->width)
		tis->ret = tfs->width;
	else
		tis->ret = tfs->flag_dot_nu;
	tfs->buf = (char *)malloc(tis->ret + 1);
	if (!tfs->buf)
		return (-1);
	init_buf(tfs, tis->ret);
	return (0);
}

int	my_putunbr(unsigned int nbr, t_flag_set *tfs)
{
	t_info_set	tis;

	tis.nbr = nbr;
	tis.base = "0123456789";
	tis.base_len = 10;
	tis.len = cnt_base(nbr, tis.base_len);
	tis.ret = tis.len;
	if (tis.ret < tfs->flag_dot_nu)
		tis.ret = tfs->flag_dot_nu;
	if (!tis.nbr && !tfs->flag_dot_nu && tfs->flag_dot)
	{
		init_precision_0(&tis, tfs);
		return (tis.ret);
	}
	mid_base(&tis, tfs);
	return (put_base(&tis, tfs));
}
