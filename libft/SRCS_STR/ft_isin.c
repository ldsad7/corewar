/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:11:24 by bsprigga          #+#    #+#             */
/*   Updated: 2018/12/04 19:36:34 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isin(char *str, char *needle)
{
	int i;
	int len_str;
	int len_needle;

	if (!*str && !*needle)
		return (1);
	len_str = ft_strlen(str);
	len_needle = ft_strlen(needle);
	i = -1;
	if (len_str < len_needle)
		return (0);
	while (++i < len_str)
	{
		if (ft_strcmp(ft_strsub(str, i, len_needle), needle) == 0)
			return (1);
	}
	return (0);
}
