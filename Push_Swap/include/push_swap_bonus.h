/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:18 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/15 22:11:24 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

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

void		init_stack(t_set_of_tb *sot, int total_element, char *data[]);
int			*make_result(int size, t_set_of_tb *sot);
void		receive_cmd(t_set_of_tb *sot);
char		*get_next_line(int fd);
void		res_check(int size, int *res, t_set_of_tb *sot);
/* cmd */
void		cmd_execute(char *cmd, t_set_of_tb *sot);
void		cmd_swap(t_stack *top);
void		cmd_rotate(t_stack **top, t_stack **bot);
void		cmd_push(t_stack **dest, t_stack **bot, t_stack **src);
void		cmd_reverse_rotate(t_stack **top, t_stack **bottom);
void		swap_node(t_stack *node1, t_stack *node2);
int			cnt_element(t_stack *top);
void		ft_swap(int *a, int *b);

/* error check */
void		max_check(char *data);
void		digit_check(char *data);
void		dup_check(t_stack *point, char *data);
void		err_exit(void);
void		ko_exit(void);

#endif