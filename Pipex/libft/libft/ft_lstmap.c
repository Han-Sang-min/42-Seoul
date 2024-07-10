/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmhan <sangmhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:43:12 by sangmhan          #+#    #+#             */
/*   Updated: 2022/07/17 14:02:56 by sangmhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*apl_lst;
	t_list	*ret;

	ret = NULL;
	while (lst)
	{
		apl_lst = ft_lstnew(f(lst->content));
		if (!apl_lst)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		ft_lstadd_back(&ret, apl_lst);
		lst = lst->next;
	}
	return (ret);
}
