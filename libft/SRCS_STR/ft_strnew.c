/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:11:30 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/16 22:20:10 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;
	size_t	max;

	max = -1;
	if (size == max)
		return (0);
	i = 0;
	str = (char *)malloc(sizeof(*str) * (size + 1));
	if (!(str))
		return (NULL);
	while (i <= size)
		str[i++] = '\0';
	return (str);
}
