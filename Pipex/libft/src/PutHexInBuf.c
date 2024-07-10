/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PutHexInBuf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:53:53 by hansangmin        #+#    #+#             */
/*   Updated: 2022/07/28 20:38:22 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	add_0x_front_of_buf(t_info_set *tis, t_flag_set *tfs, int type)
{
	char	*t_buf;

	t_buf = tfs->buf;
	if (tfs->flag_minus)
		t_buf += 0;
	else if (tfs->flag_dot_nu < tis->len)
		t_buf += tis->ret - tis->len - 2;
	else
		t_buf += tis->ret - tfs->flag_dot_nu - 2;
	if (type == HEX_S)
		ft_memcpy(t_buf, "0x", 2);
	else
		ft_memcpy(t_buf, "0X", 2);
}

int	my_puthex(unsigned int nbr, int type, t_flag_set *tfs)
{
	t_info_set	tis;

	tis.nbr = nbr;
	if (type == HEX_S)
		tis.base = "0123456789abcdef";
	else if (type == HEX_B)
		tis.base = "0123456789ABCDEF";
	tis.base_len = 16;
	tis.len = cnt_base(nbr, tis.base_len);
	tis.ret = tis.len;
	if (tis.ret < tfs->flag_dot_nu)
		tis.ret = tfs->flag_dot_nu;
	if (tfs->flag_shap && tis.nbr)
		tis.ret += 2;
	if (!tis.nbr && !tfs->flag_dot_nu && tfs->flag_dot)
	{
		init_precision_0(&tis, tfs);
		return (tis.ret);
	}
	mid_base(&tis, tfs);
	if (tfs->flag_shap && tis.nbr)
		add_0x_front_of_buf(&tis, tfs, type);
	return (put_base(&tis, tfs));
}
