/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:07:31 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/16 13:50:29 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"

void	init_struct(t_set_of_tb *sot)
{
	sot->top_a = NULL;
	sot->bot_a = NULL;
	sot->top_b = NULL;
	sot->bot_b = NULL;
}

int	main(int argc, char *argv[])
{
	t_set_of_tb	sot;
	int			*res;

	if (argc == 1)
		return (0);
	init_struct(&sot);
	init_stack(&sot, argc, argv);
	res = make_result(argc - 1, &sot);
	receive_cmd(&sot);
	res_check(argc - 1, res, &sot);
	return (0);
}
