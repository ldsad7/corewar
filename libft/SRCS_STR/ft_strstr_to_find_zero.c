/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_to_find_zero.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 20:13:54 by bsprigga          #+#    #+#             */
/*   Updated: 2019/01/29 12:27:30 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr_to_find_zero(const char *str, const char *to_find)
{
	int i;
	int j;
	int substr_len;

	i = 0;
	if (!(*to_find))
		return (0);
	substr_len = ft_strlen(to_find);
	while (str[i])
	{
		j = 0;
		while (to_find[j] && str[i + j] == to_find[j])
			j++;
		if (substr_len == j)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}
