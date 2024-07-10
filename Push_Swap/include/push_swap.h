/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:14:58 by hansangmin        #+#    #+#             */
/*   Updated: 2022/11/17 09:25:57 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/include/ft_printf.h"

/* stack info */
typedef struct s_stack
{
	int				data;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

/* set of stack */
typedef struct s_set_of_tb
{
	t_stack	*top_a;
	t_stack	*bot_a;
	t_stack	*top_b;
	t_stack	*bot_b;
}	t_set_of_tb;

typedef struct s_schedules
{
	int					size;
	char				point;
	struct s_schedules	*next;
}	t_schedules;

typedef struct s_sort_info
{
	int	pv1;
	int	pv2;
	int	size1;
	int	size2;
	int	size3;
}	t_sort_info;

void		init_stack(t_set_of_tb *sot, int total_element, char *data[]);
void		push_schd(t_schedules **schd, int size, char point);
void		pop_schd(t_schedules **schd);
void		sort_check(t_schedules *schd, t_set_of_tb *sot);

/* cmd */
void		cmd_execute(char *cmd, t_set_of_tb *sot);
void		cmd_swap(t_stack *top);
void		cmd_rotate(t_stack **top, t_stack **bot);
void		cmd_push(t_stack **dest, t_stack **bot, t_stack **src);
void		cmd_reverse_rotate(t_stack **top, t_stack **bottom);
void		swap_node(t_stack *node1, t_stack *node2);
int			cnt_element(t_stack *top);

/* sort */
t_sort_info	find_pivot(t_schedules *schd, t_set_of_tb *sot);
void		ft_swap(int *a, int *b);
void		sort_stack(t_set_of_tb *sot, t_schedules **schd);
void		b_rot(int size2, int size1, t_set_of_tb *sot);
void		a_rot(t_sort_info tsi, t_set_of_tb *sot);
void		sort_out_a1(t_sort_info *tsi, t_set_of_tb *sot, t_schedules *schd);
void		sort_out_a2(t_set_of_tb *sot, t_schedules *schd);
void		sort_out_b1(t_sort_info *tsi, t_set_of_tb *sot, t_schedules *schd);
void		sort_out_b2(t_set_of_tb *sot, t_schedules *schd);
void		b_size3_4(t_set_of_tb *sot, int size1, int size2);
void		a_size3_4(t_set_of_tb *sot, int size1, int size2);
int			is_need_rot(t_sort_info *tsi, t_set_of_tb *sot);

/* error check */
void		max_check(char *data);
void		digit_check(char *data);
void		dup_check(t_stack *point, char *data);
void		err_exit(void);

/* sort extra */
void		sort_size3(t_set_of_tb *sot);
void		sort_size5(t_set_of_tb *sot, t_schedules **schd);

#endif