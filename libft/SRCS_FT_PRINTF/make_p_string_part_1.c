/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_p_string_part_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 18:19:34 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:15:56 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	adjust_precision_p(char **str)
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

static void	adjust_width_p(char **str)
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

static void	apply_prefix_p(char **str)
{
	char	*res;

	if (g_f->curr_flags[3])
	{
		res = NULL;
		if (!(res = ft_strnew(ft_strlen(*str) + 2)))
			clear_all_exit(-1);
		res[1] = 'x';
		res[0] = '0';
		ft_strcat(res, *str);
		free(*str);
		*str = res;
	}
}

static void	apply_zero_p(char **str)
{
	int		i;
	int		j;
	char	sign;

	sign = 0;
	if (g_f->curr_flags[4] && g_f->prec_value == -1)
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

void		make_str_p(void)
{
	char				*tmp_string;
	unsigned long long	tmp;
	int					len_ini_tmp_str;

	tmp = va_arg(g_ap, size_t);
	if (!(tmp_string = ft_itoa_base_unsigned(tmp, 16)))
		clear_all_exit(-1);
	len_ini_tmp_str = ft_strlen(tmp_string);
	adjust_precision_p(&tmp_string);
	apply_prefix_p(&tmp_string);
	adjust_width_p(&tmp_string);
	apply_zero_p(&tmp_string);
	fix_prefix_16_p(&tmp_string, len_ini_tmp_str);
	upper_lower_xp(&tmp_string);
	if (!(g_f->str))
		g_f->str = tmp_string;
}
