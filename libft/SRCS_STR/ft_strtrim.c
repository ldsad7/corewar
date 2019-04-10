/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:21:17 by bsprigga          #+#    #+#             */
/*   Updated: 2018/11/30 21:40:22 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		first_symbol;
	int		len;
	char	*res;

	if (!s)
		return (0);
	i = 0;
	first_symbol = 0;
	len = ft_strlen((char *)s) - 1;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	if (s[i] && !(s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		first_symbol = i;
	while (s[len] && (s[len] == ' ' || s[len] == '\n' || s[len] == '\t'))
		len--;
	len = len - first_symbol + 1;
	res = (char *)malloc(sizeof(*res) * (len + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < len)
		res[i] = s[first_symbol + i];
	res[i] = '\0';
	return (res);
}
