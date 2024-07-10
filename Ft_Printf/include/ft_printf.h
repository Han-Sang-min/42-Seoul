/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 00:52:37 by hansangmin        #+#    #+#             */
/*   Updated: 2022/07/28 20:43:42 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>
# include "../libft/libft.h"

# define HEX_S 6
# define HEX_B 7

typedef struct s_flag_set
{
	bool	flag_minus;
	char	flag_zero;
	bool	flag_dot;
	int		flag_dot_nu;
	bool	flag_shap;
	bool	flag_space;
	bool	flag_plus;
	int		width;
	char	*buf;
}	t_flag_set;

typedef struct s_info_set
{
	long long	nbr;
	int			ret;
	int			len;
	char		*base;
	int			base_len;
}	t_info_set;

typedef struct s_mem_info
{
	size_t	nbr;
	int		ret;
	int		len;
}	t_mem_info;

int		ft_printf(const char *args, ...);
int		pnt_args(const char *args, va_list *ap, t_flag_set *tfs);
int		my_putunbr(unsigned int nbr, t_flag_set *tfs);
int		my_puthex(unsigned int nbr, int type, t_flag_set *tfs);
int		my_putmem(size_t nbr, t_flag_set *tfs);
int		my_putchar(char c, t_flag_set *tfs);
int		my_putstr(char *str, t_flag_set *tfs);
int		my_putnbr(long long nbr, t_flag_set *tfs);
int		cnt_base(long long nbr, int base);
void	write_buf(t_flag_set *tfs);
void	init_buf(t_flag_set *tfs, int len);
void	buf_nbr(long long nbr, int n_base, char *s_base, char *buf);
int		put_base(t_info_set *tis, t_flag_set *tfs);
int		mid_base(t_info_set *tis, t_flag_set *tfs);
int		init_precision_0(t_info_set *tis, t_flag_set *tfs);
void	init_struct(t_flag_set *tfs);

#endif