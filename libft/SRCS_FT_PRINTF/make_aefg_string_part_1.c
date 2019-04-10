/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_aefg_string_part_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:42:35 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:17:31 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_value_aefg(long double *tmp)
{
	if (g_f->size == L_LB)
		*tmp = (long double)va_arg(g_ap, long double);
	else
		*tmp = va_arg(g_ap, double);
}

static char	*convert_to_string_aefg(long double tmp)
{
	if (ft_strchr("aA", g_f->type))
		return (convert_af(tmp, 16));
	else
		return (convert_af(tmp, 10));
}

static void	adjust_precision_aefg(char **str)
{
	int		steps;
	char	*res;
	size_t	len_decimal;
	size_t	len_str;

	len_str = ft_strlen(*str);
	len_decimal = count_decimal_len(*str);
	if (g_f->prec_value > 0 &&
	(steps = g_f->prec_value - len_decimal) > 0)
	{
		if (!(res = ft_strnew(len_str + steps)))
			clear_all_exit(-1);
		ft_strcat(res, *str);
		while (steps--)
			res[len_str + steps] = '0';
		free(*str);
		*str = res;
	}
}

static void	adjust_width_aefg(char **str)
{
	int		steps;
	char	*res;
	size_t	len_str;

	len_str = ft_strlen(*str);
	if (g_f->width_value > -1 && (steps = g_f->width_value - (int)len_str) > 0)
	{
		if (!(res = ft_strnew(len_str + steps)))
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

void		make_str_aefg(void)
{
	char		*tmp_string;
	long double	tmp;

	tmp = 0;
	get_value_aefg(&tmp);
	if (!(tmp_string = convert_to_string_aefg(tmp)))
		clear_all_exit(-1);
	adjust_precision_aefg(&tmp_string);
	apply_plus_space_aefg(&tmp_string);
	adjust_width_aefg(&tmp_string);
	apply_zero_aefg(&tmp_string);
	upper_lower_aefg(&tmp_string);
	if (!(g_f->str))
		g_f->str = tmp_string;
}
