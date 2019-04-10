/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 20:14:19 by bsprigga          #+#    #+#             */
/*   Updated: 2018/12/06 18:40:15 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static t_list	*insert_to_list_end(t_list *res, t_list *elem)
{
	t_list *tmp;

	if (!res)
		return (elem);
	tmp = res;
	while (res->next)
		res = res->next;
	res->next = elem;
	res = tmp;
	return (res);
}

static void		del(void *res, size_t data_size)
{
	data_size = 0;
	free(res);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *res;
	t_list *temp;

	if (!lst || !f)
		return (NULL);
	res = f(lst);
	if (!res)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		temp = f(lst);
		if (!temp)
		{
			ft_lstdel(&res, del);
			return (NULL);
		}
		res = insert_to_list_end(res, temp);
		lst = lst->next;
	}
	return (res);
}
