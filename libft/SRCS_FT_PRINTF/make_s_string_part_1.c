/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_s_string_part_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 12:34:27 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:16:06 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_value_s(char **tmp1, wchar_t **tmp2)
{
	int wchar_len;
	int offset;
	int	i;

	if (g_f->size == L_L)
		*tmp2 = (va_arg(g_ap, wchar_t*));
	else
		*tmp1 = va_arg(g_ap, char*);
	if (!(*tmp1) && !(*tmp2))
		*tmp1 = ft_strdup("(null)");
	else if (*tmp1)
		*tmp1 = ft_strdup(*tmp1);
	else if (tmp2)
	{
		i = -1;
		wchar_len = wchar_strlen(*tmp2);
		offset = 0;
		if (!(*tmp1 = ft_strnew(wchar_len)))
			clear_all_exit(-1);
		while ((*tmp2)[++i])
			wchar_to_char(*tmp1, &offset, (*tmp2)[i]);
	}
}

static int	get_symbol_size(unsigned char c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0xDF)
		return (2);
	else if (c <= 0xEF)
		return (3);
	return (4);
}

static int	correct_precision_wchar(char *str)
{
	int i;
	int prec;

	i = 0;
	prec = 0;
	while (str[i])
	{
		if (prec + get_symbol_size(str[i]) <= g_f->prec_value)
		{
			prec += get_symbol_size(str[i]);
			i += get_symbol_size(str[i]);
		}
		else
			break ;
	}
	return (prec);
}

static void	adjust_precision_s(char **str)
{
	char	*res;
	int		len_str;
	int		prec;

	len_str = ft_strlen(*str);
	if (g_f->prec_value > 0 && g_f->prec_value - len_str < 0)
	{
		prec = correct_precision_wchar(*str);
		g_f->prec_value = prec;
		if (!(res = ft_strnew(g_f->prec_value)))
			clear_all_exit(-1);
		ft_strncpy(res, *str, g_f->prec_value);
		free(*str);
		*str = res;
	}
	else if (g_f->prec_value == 0)
	{
		free(*str);
		*str = NULL;
		if (!(*str = ft_strnew(0)))
			clear_all_exit(-1);
	}
}

void		make_str_s(void)
{
	wchar_t	*wchar_string;
	char	*char_string;

	char_string = NULL;
	wchar_string = NULL;
	get_value_s(&char_string, &wchar_string);
	if (wchar_string && check_exclusion_symbols(wchar_string))
	{
		g_f->str = ft_strdup("");
		g_count = -1;
		return ;
	}
	adjust_precision_s(&char_string);
	adjust_width_s(&char_string);
	apply_zero_s(&char_string);
	g_f->str = char_string;
}
