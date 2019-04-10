/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_s_string_part_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 12:34:27 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:16:10 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	adjust_width_s(char **str)
{
	int		steps;
	char	*res;
	size_t	len_str;

	len_str = ft_strlen(*str);
	if (g_f->width_value > -1 && (steps = g_f->width_value - (int)len_str) > 0)
	{
		if (!(res = ft_strnew(steps + len_str)))
			clear_all_exit(-1);
		if (g_f->curr_flags[0])
		{
			ft_strcat(res, *str);
			while (steps--)
				res[len_str + steps] = ' ';
		}
		else
		{
			while (steps--)
				res[steps] = ' ';
			ft_strcat(res, *str);
		}
		free(*str);
		*str = res;
	}
}

void	apply_zero_s(char **str)
{
	int		i;
	char	sign;

	sign = 0;
	if (g_f->curr_flags[4] && !(g_f->curr_flags[0]))
	{
		i = -1;
		while ((*str)[++i] == ' ')
			(*str)[i] = '0';
	}
}

int		check_exclusion_symbols(wchar_t *str)
{
	while (*str)
	{
		if (((unsigned)*str >= 0xd800 && (unsigned)*str <= 0xdfff) ||
		(unsigned)*str > 0x10ffff)
			return (1);
		str++;
	}
	return (0);
}
