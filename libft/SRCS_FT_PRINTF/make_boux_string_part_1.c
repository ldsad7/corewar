/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_boux_string_part_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:42:35 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:14:53 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		get_value_boux(unsigned long long *tmp)
{
	int size_flags;

	size_flags = 0;
	if (g_f->size > L_NONE)
	{
		g_f->size == L_L ? *tmp = va_arg(g_ap, unsigned long) : 1;
		g_f->size == L_LL ? *tmp = va_arg(g_ap, unsigned long long) : 1;
		g_f->size == L_H ? *tmp = (unsigned short)va_arg(g_ap, unsigned) : 1;
		g_f->size == L_HH ? *tmp = (unsigned char)va_arg(g_ap, unsigned) : 1;
		g_f->size == L_J ? *tmp = va_arg(g_ap, uintmax_t) : 1;
		g_f->size == L_Z ? *tmp = va_arg(g_ap, size_t) : 1;
		g_f->size == L_T ? *tmp = va_arg(g_ap, unsigned long long) : 1;
		size_flags = 1;
	}
	if (!size_flags)
		*tmp = va_arg(g_ap, unsigned int);
}

static char		*convert_to_string_boux(unsigned long long *tmp)
{
	if (ft_strchr("b", g_f->type))
		return (ft_itoa_base(*tmp, 2));
	if (ft_strchr("xX", g_f->type))
		return (ft_itoa_base_unsigned(*tmp, 16));
	if (ft_strchr("o", g_f->type))
		return (ft_itoa_base_unsigned(*tmp, 8));
	return (ft_itoa_base_unsigned(*tmp, 10));
}

static void		adjust_precision_boux(char **str)
{
	int		steps;
	char	*res;
	size_t	len_str;

	(g_f->prec_value == 0 && ft_strcmp(*str, "0") == 0) ? *str[0] = '\0' : '\0';
	len_str = ft_strlen(*str);
	if (g_f->prec_value > -1 && (steps = g_f->prec_value - len_str) >= 0)
	{
		if (*str[0] == '-')
			steps++;
		if (!(res = ft_strnew(steps + len_str)))
			clear_all_exit(-1);
		while (steps--)
			res[steps] = '0';
		if (*str[0] == '-')
		{
			res[0] = '-';
			ft_strcat(res, "0");
			ft_strcat(res, *str + 1);
		}
		else
			ft_strcat(res, *str);
		free(*str);
		*str = res;
	}
}

static void		adjust_width_boux(char **str)
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

void			make_str_boux(void)
{
	char				*tmp_string;
	unsigned long long	tmp;
	char				num_sys;
	int					len_ini_tmp_str;

	tmp = 0;
	get_value_boux(&tmp);
	if (!(tmp_string = convert_to_string_boux(&tmp)))
		clear_all_exit(-1);
	len_ini_tmp_str = ft_strlen(tmp_string);
	adjust_precision_boux(&tmp_string);
	num_sys = apply_prefix_boux(&tmp_string, tmp);
	adjust_width_boux(&tmp_string);
	apply_zero_boux(&tmp_string);
	fix_prefix_2_16_boux(&tmp_string, num_sys, len_ini_tmp_str);
	upper_lower_xp(&tmp_string);
	if (!(g_f->str))
		g_f->str = tmp_string;
}
