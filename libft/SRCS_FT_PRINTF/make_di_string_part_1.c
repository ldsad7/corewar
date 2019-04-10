/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_di_string_part_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 12:34:27 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:15:29 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_value_di(long long *tmp)
{
	if (g_f->size > L_NONE)
	{
		g_f->size == L_L ? *tmp = va_arg(g_ap, long int) : 1;
		g_f->size == L_LL ? *tmp = va_arg(g_ap, long long) : 1;
		g_f->size == L_H ? *tmp = (short int)va_arg(g_ap, int) : 1;
		g_f->size == L_HH ? *tmp = (char)va_arg(g_ap, int) : 1;
		g_f->size == L_J ? *tmp = va_arg(g_ap, intmax_t) : 1;
		g_f->size == L_Z ? *tmp = va_arg(g_ap, size_t) : 1;
		g_f->size == L_T ? *tmp = va_arg(g_ap, long long) : 1;
	}
	else
		*tmp = va_arg(g_ap, int);
}

static void	adjust_precision_di(char **str)
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

static void	adjust_width_di(char **str)
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

static void	apply_plus_space_di(char **str)
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

void		make_str_di(void)
{
	char		*tmp_string;
	long long	tmp;

	if (g_f->str)
		tmp_string = g_f->str;
	else
	{
		tmp = 0;
		get_value_di(&tmp);
		if (!(tmp_string = ft_itoa_long(tmp)))
			clear_all_exit(-1);
	}
	adjust_precision_di(&tmp_string);
	apply_plus_space_di(&tmp_string);
	adjust_width_di(&tmp_string);
	apply_zero_di(&tmp_string);
	g_f->str = tmp_string;
}
