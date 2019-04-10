/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_append_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 19:21:33 by bsprigga          #+#    #+#             */
/*   Updated: 2019/01/28 15:12:38 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_append_str(char **str1, char **str2)
{
	char	*res;
	int		len1;
	int		len2;

	len1 = (*str1) ? ft_strlen(*str1) : 0;
	len2 = (*str2) ? ft_strlen(*str2) : 0;
	if (!(res = ft_strnew(sizeof(char) * (len1 + len2))))
		return (NULL);
	len1 ? ft_strcpy(res, *str1) : NULL;
	len2 ? ft_strcpy(&(res[len1]), *str2) : NULL;
	free(*str1);
	free(*str2);
	*str1 = NULL;
	*str2 = NULL;
	return (res);
}
