/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:54:28 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/03 01:43:53 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*cp;
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	cp = (char *)ft_strnew(sizeof(*cp) * len);
	if (cp == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cp[i] = src[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}
