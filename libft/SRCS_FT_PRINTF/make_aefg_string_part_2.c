/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_aefg_string_part_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:42:35 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:14:32 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		apply_plus_space_aefg(char **str)
{
	char *res;

	if (g_f->curr_flags[1] && *str[0] != '-')
	{
		if (!(res = ft_strnew(ft_strlen(*str) + 1)))
			clear_all_exit(-1);
		res[0] = '+';
		ft_strcat(res, *str);
		free(*str);
		*str = res;
	}
	else if (g_f->curr_flags[2] && *str[0] != '-')
	{
		if (!(res = ft_strnew(ft_strlen(*str) + 1)))
			clear_all_exit(-1);
		res[0] = ' ';
		ft_strcat(res, *str);
		free(*str);
		*str = res;
	}
}

void		apply_zero_aefg(char **str)
{
	int		i;
	int		j;
	char	sign;

	sign = 0;
	if (g_f->curr_flags[4] && !(g_f->curr_flags[0])
	&& g_f->width_value > g_f->prec_value)
	{
		i = -1;
		while (ft_strchr("+- ", (*str)[++i]))
			if (ft_strchr("+-", (*str)[i]))
				sign = (*str)[i];
		j = 0;
		if (sign)
		{
			(*str)[0] = sign;
			j++;
		}
		while (j < i)
			(*str)[j++] = '0';
	}
}

void		upper_lower_aefg(char **str)
{
	int i;

	i = -1;
	if (g_f->type == 'F')
		while ((*str)[++i])
			(*str)[i] = ft_toupper((*str)[i]);
}

static char	*round(long double tmp, int base, int i)
{
	long long	tmp_cp;

	while (--i > -1)
		tmp *= base;
	if ((tmp - (long long)tmp) < 0.5)
		return (ft_itoa_base((long long)tmp, base));
	else
	{
		tmp_cp = (long long)tmp;
		tmp -= (long long)tmp;
		i = 8;
		while (--i > -1)
		{
			tmp *= base;
			if ((long long)tmp == 0)
				continue ;
			else if ((long long)tmp < 5)
				return (ft_itoa_base(tmp_cp, base));
			else
				return (ft_itoa_base(tmp_cp + 1, base));
		}
		return (ft_itoa_base(tmp_cp, base));
	}
}

char		*convert_af(long double tmp, int base)
{
	char	*res;
	char	*tmp_round;

	if (ft_isnan(tmp) || ft_isinf(tmp))
	{
		res = write_nan_inf(tmp);
		return (res);
	}
	if (g_f->prec_value == -1)
		g_f->prec_value = 6;
	if (!(res = ft_itoa_base((long long)tmp, base)))
		clear_all_exit(-1);
	tmp -= (long long)tmp;
	if ((g_f->prec_value > 0) ||
	(g_f->prec_value == 0 && g_f->curr_flags[3]))
	{
		(tmp < 0) ? tmp *= -1 : 1;
		if (!(res = ft_str_append_char(&res, '.')) ||
		!(tmp_round = round(tmp, base, g_f->prec_value)))
			clear_all_exit(-1);
		if (tmp > 0 && g_f->prec_value > 0)
			res = ft_str_append_str(&res, &tmp_round);
		free(tmp_round);
	}
	return (res);
}
