/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:28:20 by bsprigga          #+#    #+#             */
/*   Updated: 2018/12/06 11:36:27 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	i;
	int		len_to_cat;

	i = 0;
	len_dst = 0;
	while (dst[i] && i < size)
	{
		len_dst++;
		i++;
	}
	if (size - i == 0)
		return (size + ft_strlen(src));
	i = -1;
	len_to_cat = size - len_dst - 1;
	while (src[++i] && len_to_cat-- > 0)
		dst[len_dst + i] = src[i];
	dst[len_dst + i] = '\0';
	return (len_dst + ft_strlen(src));
}
