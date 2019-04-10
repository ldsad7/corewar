/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_natural_pow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:49:28 by bsprigga          #+#    #+#             */
/*   Updated: 2018/12/04 20:51:34 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long int	ft_natural_pow(int base, int pow)
{
	int i;
	int base_ini;

	if (pow < 0)
		return (0);
	if (pow == 0)
		return (1);
	base_ini = base;
	i = -1;
	while (++i < pow)
		base *= base_ini;
	return (base);
}
