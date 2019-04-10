/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:21:23 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/02 19:28:21 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

void	ft_strdel(char **as)
{
	char *tmp;

	tmp = *as;
	if (!as || !*as)
		return ;
	while (**as)
	{
		**as = '\0';
		*as += 1;
	}
	free(tmp);
	*as = NULL;
}
