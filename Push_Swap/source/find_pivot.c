/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pivot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:53:18 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/17 09:26:22 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	cpy_list(int *arr, t_schedules *schd, t_set_of_tb *sot)
{
	int		idx;
	t_stack	*point;

	if (schd->point == 'A')
		point = sot->top_a;
	else
		point = sot->top_b;
	idx = -1;
	while (++idx < schd->size)
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

t_sort_info	find_pivot(t_schedules *schd, t_set_of_tb *sot)
{
	int			*arr;
	t_sort_info	ret;

	arr = (int *)malloc(sizeof(int) * schd->size);
	if (!arr)
		exit(1);
	cpy_list(arr, schd, sot);
	quick_sort(arr, 0, schd->size - 1);
	ret.pv1 = arr[schd->size - schd->size / 3 - 1];
	ret.pv2 = arr[schd->size / 3];
	ret.size1 = schd->size / 3;
	ret.size2 = schd->size - schd->size / 3 - 1 - schd->size / 3;
	ret.size3 = schd->size / 3 + 1;
	free(arr);
	return (ret);
}

void	sort_check(t_schedules *schd, t_set_of_tb *sot)
{
	t_stack			*st;
	int				idx;
	int				*arr;

	arr = (int *)malloc(sizeof(int) * schd->size);
	if (!arr)
		exit(1);
	cpy_list(arr, schd, sot);
	quick_sort(arr, 0, schd->size - 1);
	idx = -1;
	st = sot->bot_a;
	while (++idx < schd->size)
	{
		if (arr[idx] != st->data)
			return ;
		st = st->next;
	}
	exit(1);
}
