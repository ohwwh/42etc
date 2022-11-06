/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:37:40 by ohw               #+#    #+#             */
/*   Updated: 2021/11/30 20:22:21 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*new;

	ret = 0;
	while (lst)
	{
		new = ft_lstnew(f(lst -> content));
		if (new)
			ft_lstadd_back(&ret, new);
		else
		{
			ft_lstclear(&ret, del);
			return (ret);
		}
		lst = lst -> next;
	}
	return (ret);
}
