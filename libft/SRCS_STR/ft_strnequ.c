/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:59:25 by bsprigga          #+#    #+#             */
/*   Updated: 2018/12/04 17:58:22 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	i = 0;
	if (s1 == 0 || s2 == 0)
	{
		if (s1 == s2)
			return (1);
		else
			return (0);
	}
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	if ((s1[i] == '\0' && s2[i] == '\0') || s1[i] == s2[i] || n == 0)
		return (1);
	return (0);
}
