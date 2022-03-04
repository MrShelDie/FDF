/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:39:39 by gannemar          #+#    #+#             */
/*   Updated: 2022/03/03 17:15:24 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*current;

	if (!lst)
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
	{
		ft_lstclear(&new_list, del);
		return (NULL);
	}
	current = new_list;
	lst = lst -> next;
	while (lst)
	{
		current -> next = ft_lstnew(f(lst -> content));
		current = current -> next;
		if (!current)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		lst = lst -> next;
	}
	return (new_list);
}
