/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PutStrInBuf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:29:37 by hansangmin        #+#    #+#             */
/*   Updated: 2022/07/28 20:38:38 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	my_putstr(char *str, t_flag_set *tfs)
{
	int	len;
	int	ret;

	if (!str)
		len = 6;
	else
		len = ft_strlen(str);
	if (tfs->flag_dot_nu < len && tfs->flag_dot)
		len = tfs->flag_dot_nu;
	ret = len;
	if (ret < tfs->width)
		ret = tfs->width;
	tfs->buf = (char *)malloc(ret + 1);
	if (!tfs->buf)
		return (-1);
	init_buf(tfs, ret);
	if (!str)
		str = "(null)";
	if (tfs->flag_minus)
		ft_memcpy(tfs->buf, str, len);
	else
		ft_memcpy(tfs->buf + ret - len, str, len);
	return (ret);
}
