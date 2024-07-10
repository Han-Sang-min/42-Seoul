/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:12 by hansangmin        #+#    #+#             */
/*   Updated: 2022/11/17 09:27:02 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

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
	t_schedules	*schd;

	schd = NULL;
	if (argc == 1)
		return (0);
	init_struct(&sot);
	init_stack(&sot, argc, argv);
	push_schd(&schd, argc - 1, 'A');
	sort_check(schd, &sot);
	if (argc == 4)
		sort_size3(&sot);
	else if (argc == 6)
		sort_size5(&sot, &schd);
	else
		sort_stack(&sot, &schd);
	cmd_execute("end", &sot);
}
