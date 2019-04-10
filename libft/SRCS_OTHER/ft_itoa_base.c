/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:44:55 by bsprigga          #+#    #+#             */
/*   Updated: 2019/01/18 16:14:25 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	start_values(int *i, long long n, long long *n_ini, int *is_neg)
{
	*n_ini = n;
	*i = 1;
	*is_neg = 1;
	if (n < 0)
	{
		*i += *is_neg;
		*is_neg = -1;
	}
}

char		*ft_itoa_base(long long n, int base)
{
	char		*res;
	int			i;
	int			is_negative;
	long long	n_ini;

	start_values(&i, n, &n_ini, &is_negative);
	while ((n_ini = n_ini / base))
		i++;
	res = (char *)ft_strnew(sizeof(*res) * i);
	if (!res)
		return (0);
	while ((--i) > -1)
	{
		if (n % base > 9)
			res[i] = (n % base) * is_negative + 'A' - 10;
		else
			res[i] = (n % base) * is_negative + '0';
		n /= base;
	}
	if (is_negative == -1)
		res[0] = '-';
	return (res);
}
