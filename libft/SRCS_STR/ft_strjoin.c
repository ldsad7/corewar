/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:49:42 by bsprigga          #+#    #+#             */
/*   Updated: 2018/12/17 18:16:12 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;
	size_t	len;
	char	*res;

	if (!s1)
		return (0);
	if (!s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len = len_s1 + len_s2;
	if (!(res = (char *)ft_strnew(sizeof(*res) * len)))
		return (0);
	i = -1;
	while (++i < len_s1)
		res[i] = s1[i];
	i--;
	while (++i < len)
		res[i] = s2[i - len_s1];
	return (res);
}
