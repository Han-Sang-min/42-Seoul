/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_sort2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:33:22 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/13 02:40:32 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	b_size3_4(t_set_of_tb *sot, int size1, int size2)
{
	while (size1 || size2)
	{
		if (!size1 || (size2 && sot->bot_a->data < sot->top_b->data))
		{
			cmd_execute("pa", sot);
			size2--;
		}
		else
		{
			cmd_execute("rra", sot);
			size1--;
		}
	}
}
