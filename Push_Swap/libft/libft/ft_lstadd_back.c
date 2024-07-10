/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 12:09:01 by sangmhan          #+#    #+#             */
/*   Updated: 2022/10/05 16:52:08 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *t_new)
{
	if (*lst == NULL)
	{
		*lst = t_new;
		return ;
	}
	if (t_new == NULL)
		return ;
	ft_lstlast(*lst)->next = t_new;
}
