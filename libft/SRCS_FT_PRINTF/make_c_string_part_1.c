/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_c_string_part_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 12:34:27 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:15:20 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_value_c(char **char_string, wint_t *wc)
{
	int		wint_len;
	int		offset;
	char	c;

	if (g_f->size == L_L)
	{
		*wc = va_arg(g_ap, wint_t);
		wint_len = wint_size(*wc);
		offset = 0;
		if (!(*char_string = ft_strnew(wint_len)))
			clear_all_exit(-1);
		wchar_to_char(*char_string, &offset, *wc);
	}
	else
	{
		if (g_f->type == '%')
			c = '%';
		else
			c = (char)va_arg(g_ap, int);
		if (!(*char_string = ft_strnew(1)))
			clear_all_exit(-1);
		(*char_string)[0] = c;
	}
}

static void	adjust_width_c(char **str)
{
	int		steps;
	char	*res;
	size_t	len_str;

	len_str = ft_strlen(*str);
	if (g_f->width_value > 0 && (steps = g_f->width_value - (int)len_str) > 0)
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

static void	apply_zero_c(char **str)
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

void		make_str_c(void)
{
	wint_t	wc;
	char	*char_string;

	wc = '\0';
	if (!(g_f->str))
		get_value_c(&char_string, &wc);
	else
		char_string = g_f->str;
	if (check_exclusion_symbol(wc))
	{
		g_f->str = ft_strdup("");
		g_count = -1;
		return ;
	}
	if (!(ft_strlen(char_string) == 0 && char_string[0] == '\0'))
	{
		adjust_width_c(&char_string);
		apply_zero_c(&char_string);
		g_f->str = char_string;
		return ;
	}
	adjust_width_c_null(&char_string);
	apply_zero_c(&char_string);
	g_f->str = char_string;
}
