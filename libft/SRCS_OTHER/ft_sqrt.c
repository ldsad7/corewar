/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 13:29:32 by bsprigga          #+#    #+#             */
/*   Updated: 2018/12/03 14:32:12 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_sqrt(int nb)
{
	double	lo;
	double	hi;
	double	mid;
	int		i;

	lo = 0;
	hi = nb / 2;
	i = -1;
	while (++i < 1000)
	{
		mid = (lo + hi) / 2;
		if (mid * mid == nb)
			return (mid);
		if (mid * mid > nb)
			hi = mid;
		else
			lo = mid;
	}
	return (mid);
}
