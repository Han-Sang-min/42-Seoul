/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:39:38 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/16 14:00:28 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"
#include <limits.h>

void	digit_check(char *data)
{
	char	*tmp;

	tmp = data;
	if (*tmp == '-' || *tmp == '+')
		++tmp;
	while (*tmp)
	{
		if (!ft_isdigit(*tmp))
			err_exit();
		tmp++;
	}
}

void	max_check(char *data)
{
	long long	tmp;

	tmp = ft_atoi(data);
	if (tmp < INT_MIN || tmp > INT_MAX)
		err_exit();
}

void	dup_check(t_stack *point, char *data)
{
	int	tmp;

	tmp = ft_atoi(data);
	while (point)
	{
		if (point->data == tmp)
			err_exit();
		point = point->prev;
	}
}
