/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:42:08 by hansangmin        #+#    #+#             */
/*   Updated: 2022/11/13 02:56:14 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	write_buf(t_flag_set *tfs)
{
	char	*t_buf;

	t_buf = tfs->buf;
	while (*t_buf)
		write(1, t_buf++, 1);
	free(tfs->buf);
}

void	init_struct2(t_flag_set *tfs)
{
	tfs->flag_minus = false;
	tfs->flag_zero = ' ';
	tfs->flag_dot = false;
	tfs->flag_dot_nu = 0;
	tfs->flag_shap = false;
	tfs->flag_space = false;
	tfs->flag_plus = false;
	tfs->width = 0;
}

void	buf_nbr(long long nbr, int n_base, char *s_base, char *buf)
{
	if (nbr < n_base)
	{
		*buf = s_base[nbr % n_base];
		return ;
	}
	buf_nbr(nbr / n_base, n_base, s_base, buf - 1);
	*buf = s_base[nbr % n_base];
}

void	init_buf(t_flag_set *tfs, int len)
{
	char	*t_buf;

	t_buf = tfs->buf;
	t_buf[len] = 0;
	while (len--)
		t_buf[len] = tfs->flag_zero;
}
