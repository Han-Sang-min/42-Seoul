/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PutCharInBuf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:28:52 by hansangmin        #+#    #+#             */
/*   Updated: 2022/07/28 20:38:45 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	my_putchar(char c, t_flag_set *tfs)
{
	int	len;

	len = 1;
	if (tfs->width > len)
		len = tfs->width;
	tfs->buf = (char *)malloc(len + 1);
	if (!tfs->buf)
		return (-1);
	init_buf(tfs, len);
	if (!ft_isprint(c))
	{
		if (tfs->flag_minus)
			write(1, &c, 1);
		write(1, tfs->buf, len - 1);
		if (!tfs->flag_minus)
			write(1, &c, 1);
		tfs->buf[0] = 0;
	}
	else if (tfs->flag_minus)
		tfs->buf[0] = c;
	else
		tfs->buf[len - 1] = c;
	return (len);
}
