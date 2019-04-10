/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:13:25 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/01 14:48:42 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	 line 28 - decrease number on power of 2
*/

unsigned int	ft_log2(unsigned int val)
{
	unsigned int	ret;

	ret = 0;
	if (val == 0)
		return (4294967295);
	if (val == 1)
		return (0);
	while (val > 1)
	{
		val >>= 1;
		ret++;
	}
	return (ret);
}
