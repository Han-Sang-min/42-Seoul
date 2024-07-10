/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PutNbrInBuf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 09:40:02 by hansangmin        #+#    #+#             */
/*   Updated: 2022/07/28 20:26:04 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	add_sign(t_info_set *tis, t_flag_set *tfs)
{
	char	*t_buf;
	char	sign;

	sign = 0;
	t_buf = tfs->buf;
	if (tis->nbr < 0)
	{
		tis->nbr *= -1;
		sign = '-';
	}
	else if (tfs->flag_plus)
		sign = '+';
	else if (tfs->flag_space)
		sign = ' ';
	if (!sign)
		return (0);
	if (tfs->flag_minus || (tis->ret == tfs->width && tfs->flag_zero == '0'))
		*t_buf = sign;
	else if (tis->len < tfs->flag_dot_nu)
		t_buf[tis->ret - tfs->flag_dot_nu - 1] = sign;
	else
		t_buf[tis->ret - tis->len - 1] = sign;
	return (sign);
}

int	my_putnbr(long long nbr, t_flag_set *tfs)
{
	t_info_set	tis;

	tis.nbr = nbr;
	tis.base = "0123456789";
	tis.base_len = 10;
	tis.len = cnt_base(tis.nbr, tis.base_len);
	tis.ret = tis.len;
	if (tis.ret < tfs->flag_dot_nu)
		tis.ret = tfs->flag_dot_nu;
	if (tis.nbr < 0 || tfs->flag_plus || tfs->flag_space)
		tis.ret += 1;
	if (!tis.nbr && !tfs->flag_dot_nu && tfs->flag_dot)
	{
		init_precision_0(&tis, tfs);
		return (tis.ret);
	}
	mid_base(&tis, tfs);
	if (add_sign(&tis, tfs) && tfs->flag_minus)
	{
		(tfs->buf) += 1;
		tis.ret = put_base(&tis, tfs);
		(tfs->buf) -= 1;
		return (tis.ret);
	}
	return (put_base(&tis, tfs));
}
