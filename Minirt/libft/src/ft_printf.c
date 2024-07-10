/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:53:51 by sangmhan          #+#    #+#             */
/*   Updated: 2022/07/26 17:34:55 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_printf(const char *args, ...)
{
	va_list		ap;
	int			cnt;
	t_flag_set	tfs;

	va_start(ap, args);
	cnt = pnt_args(args, &ap, &tfs);
	va_end(ap);
	return (cnt);
}
