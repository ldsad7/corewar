/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_append_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 19:21:33 by bsprigga          #+#    #+#             */
/*   Updated: 2019/01/25 17:13:25 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_append_char(char **str, char c)
{
	char	*res;
	int		len_ini;

	len_ini = ft_strlen(*str);
	if (!(res = ft_strnew(sizeof(char) * (len_ini + 1))))
		return (NULL);
	ft_strcpy(res, *str);
	res[len_ini] = c;
	free(*str);
	*str = NULL;
	return (res);
}
