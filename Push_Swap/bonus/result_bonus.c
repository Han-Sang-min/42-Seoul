/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:26:36 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/15 22:09:13 by sangmiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"

void	res_check(int size, int *res, t_set_of_tb *sot)
{
	t_stack			*st;
	int				idx;

	idx = -1;
	st = sot->bot_a;
	while (++idx < size)
	{
		if (res[idx] != st->data)
			ko_exit();
		st = st->next;
	}
	write(1, "OK\n", 3);
}

void	cpy_list(int *arr, int size, t_set_of_tb *sot)
{
	const t_stack	*point = sot->top_a;
	int				idx;

	idx = -1;
	while (++idx < size)
	{
		arr[idx] = point->data;
		point = point->prev;
	}
}

void	quick_sort(int *arr, int left, int right)
{
	int	pivot;
	int	l;
	int	r;

	l = left;
	r = right;
	pivot = arr[left];
	while (l <= r)
	{
		while (arr[l] > pivot)
			l++;
		while (arr[r] < pivot)
			r--;
		if (l <= r)
			ft_swap(&arr[l++], &arr[r--]);
	}
	if (left < r)
		quick_sort(arr, left, r);
	if (right > l)
		quick_sort(arr, l, right);
}

int	*make_result(int size, t_set_of_tb *sot)
{
	int			*arr;

	arr = (int *)malloc(sizeof(int) * size);
	if (!arr)
		exit(1);
	cpy_list(arr, size, sot);
	quick_sort(arr, 0, size - 1);
	return (arr);
}
