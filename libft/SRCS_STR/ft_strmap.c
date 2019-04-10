/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:48:04 by bsprigga          #+#    #+#             */
/*   Updated: 2018/11/30 21:37:58 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	int		len;
	char	*res;

	if (!s)
		return (0);
	len = ft_strlen((char *)s);
	res = (char *)ft_strnew(sizeof(*res) * (len));
	if (!res)
		return (0);
	i = -1;
	while (s[++i])
		res[i] = f(s[i]);
	return (res);
}
