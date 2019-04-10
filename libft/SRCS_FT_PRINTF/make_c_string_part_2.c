/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_c_string_part_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 12:34:27 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:15:25 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	f_null_wo_width(char **str)
{
	char	*res;

	g_f->null_c_len = 1;
	if (!(res = ft_strnew(1)))
		clear_all_exit(-1);
	res[0] = '\0';
	free(*str);
	*str = res;
}

void		adjust_width_c_null(char **str)
{
	int		steps;
	char	*res;

	if ((steps = g_f->width_value - 1) <= 0)
		return (f_null_wo_width(str));
	if (!(res = ft_strnew(steps + 1)))
		clear_all_exit(-1);
	g_f->null_c_len = steps + 1;
	if (g_f->curr_flags[0])
	{
		res[0] = '\0';
		while (steps--)
			res[1 + steps] = ' ';
	}
	else
	{
		res[steps] = '\0';
		while (steps--)
			res[steps] = ' ';
	}
	free(*str);
	*str = res;
}

int			check_exclusion_symbol(wint_t c)
{
	if (((unsigned)c >= 0xd800 && (unsigned)c <= 0xdfff) ||
	(unsigned)c > 0x10ffff)
		return (1);
	return (0);
}
