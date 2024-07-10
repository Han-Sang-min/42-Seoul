/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PntArgs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:32:10 by sangmhan          #+#    #+#             */
/*   Updated: 2022/07/28 20:57:34 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

const char	*flag_dot_turntrue(const char *args, t_flag_set *tfs)
{
	tfs->flag_dot = true;
	tfs->flag_dot_nu = ft_atoi(++args);
	if (tfs->flag_dot_nu)
		args += cnt_base(tfs->flag_dot_nu, 10) - 1;
	else
		args--;
	return (args);
}

static const char	*ck_flag(const char *args, t_flag_set *tfs)
{
	while (*args == '-' || *args == '0' || *args == '.' || \
	*args == '#' || *args == ' ' || *args == '+')
	{
		if (*args == '-')
			tfs->flag_minus = true;
		else if (*args == '0')
			tfs->flag_zero = '0';
		else if (*args == '.')
			args = flag_dot_turntrue(args, tfs);
		else if (*args == '#')
			tfs->flag_shap = true;
		else if (*args == ' ')
			tfs->flag_space = true;
		else if (*args == '+')
			tfs->flag_plus = true;
		args++;
	}
	if (tfs->flag_dot_nu || tfs->flag_minus)
		tfs->flag_zero = ' ';
	if (tfs->flag_plus)
		tfs->flag_space = false;
	return (args);
}

static const char	*ck_width(const char *args, t_flag_set *tfs)
{
	while (*args >= '0' && *args <= '9')
		tfs->width = tfs->width * 10 + *args++ - '0';
	return (args);
}

static int	pnt_element(char type, va_list *ap, int *cnt, t_flag_set *tfs)
{
	int	t_cnt;

	t_cnt = *cnt;
	if (type == 'c')
		*cnt += my_putchar(va_arg(*ap, int), tfs);
	else if (type == 's')
		*cnt += my_putstr(va_arg(*ap, char *), tfs);
	else if (type == 'p')
		*cnt += my_putmem(va_arg(*ap, unsigned long long), tfs);
	else if (type == 'd')
		*cnt += my_putnbr(va_arg(*ap, int), tfs);
	else if (type == 'i')
		*cnt += my_putnbr(va_arg(*ap, int), tfs);
	else if (type == 'u')
		*cnt += my_putunbr(va_arg(*ap, unsigned int), tfs);
	else if (type == 'x')
		*cnt += my_puthex(va_arg(*ap, unsigned int), HEX_S, tfs);
	else if (type == 'X')
		*cnt += my_puthex(va_arg(*ap, unsigned int), HEX_B, tfs);
	else if (type == '%')
		*cnt += my_putchar('%', tfs);
	if (*cnt < t_cnt)
		return (-1);
	write_buf(tfs);
	return (0);
}

int	pnt_args(const char *args, va_list *ap, t_flag_set *tfs)
{
	int	ret;

	ret = 0;
	while (*args)
	{
		if (*args == '%')
		{
			init_struct(tfs);
			args = ck_flag(++args, tfs);
			args = ck_width(args, tfs);
			args = ck_flag(args, tfs);
			if (pnt_element(*args, ap, &ret, tfs) == -1)
				return (-1);
		}
		else
		{
			write(1, args, 1);
			ret++;
		}
		args++;
	}
	return (ret);
}
