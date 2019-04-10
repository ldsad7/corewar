/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 20:13:02 by bsprigga          #+#    #+#             */
/*   Updated: 2018/12/06 11:51:08 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	start_values(int *i, int n, int *n_ini, int *is_negative)
{
	*n_ini = n;
	*i = 1;
	*is_negative = 1;
	if (n < 0)
	{
		*i += *is_negative;
		*is_negative = -1;
	}
}

char		*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		is_negative;
	int		n_ini;

	start_values(&i, n, &n_ini, &is_negative);
	while ((n_ini = n_ini / 10))
		i++;
	res = (char *)ft_strnew(sizeof(*res) * i);
	if (!res)
		return (0);
	while ((--i) > -1)
	{
		res[i] = (n % 10) * is_negative + '0';
		n /= 10;
	}
	if (is_negative == -1)
		res[0] = '-';
	return (res);
}
