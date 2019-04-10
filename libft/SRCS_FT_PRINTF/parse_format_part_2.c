/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format_part_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 18:49:10 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:16:22 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			parse_width(const char *format_i)
{
	char	*width;
	int		i;

	i = 0;
	if (format_i[0] == '*')
	{
		i++;
		if ((g_f->width_value = va_arg(g_ap, int)) < 0)
		{
			g_f->width_value *= -1;
			g_f->curr_flags[0] = 1;
		}
	}
	if (format_i[i] >= '1' && format_i[i] <= '9')
	{
		!(width = ft_strnew(0)) ? clear_all_exit(-1) : 1;
		while (format_i[i] >= '0' && format_i[i] <= '9')
		{
			width = ft_str_append_char(&width, format_i[i]);
			i++;
		}
		g_f->width_value = ft_atoi(width);
		free(width);
	}
	return (i);
}

int			parse_precision(const char *format_i)
{
	char	*precision;
	int		i;

	i = 0;
	if (!(format_i[i] == '.'))
		return (0);
	g_f->prec_value = 0;
	if (format_i[++i] == '*')
	{
		g_f->prec_value = va_arg(g_ap, int);
		i++;
	}
	else if (format_i[i] >= '0' && format_i[i] <= '9')
	{
		if (!(precision = ft_strnew(0)))
			clear_all_exit(-1);
		while (format_i[i] >= '0' && format_i[i] <= '9')
		{
			precision = ft_str_append_char(&precision, format_i[i]);
			i++;
		}
		g_f->prec_value = ft_atoi(precision);
		free(precision);
	}
	return (i);
}

static void	check_size(enum e_size l, int *plus_i)
{
	if (l > g_f->size)
		g_f->size = l;
	if (l == L_H || l == L_J || l == L_Z || l == L_T || l == L_L || l == L_LB)
		*plus_i = 1;
	else if (l == L_HH || l == L_LL)
		*plus_i = 2;
}

int			parse_size(const char *format_i)
{
	int plus_i;

	plus_i = 0;
	if (*format_i == 'L')
		check_size(L_LB, &plus_i);
	else if (*format_i == 'h' && *(format_i + 1) != 'h')
		check_size(L_H, &plus_i);
	else if (*format_i == 'h' && *(format_i + 1) == 'h')
		check_size(L_HH, &plus_i);
	else if (*format_i == 'l' && *(format_i + 1) != 'l')
		check_size(L_L, &plus_i);
	else if (*format_i == 'l' && *(format_i + 1) == 'l')
		check_size(L_LL, &plus_i);
	else if (*format_i == 'j')
		check_size(L_J, &plus_i);
	else if (*format_i == 't')
		check_size(L_T, &plus_i);
	else if (*format_i == 'z')
		check_size(L_Z, &plus_i);
	return (plus_i);
}

int			parse_type(const char *format_i, int *spec_end)
{
	if (*format_i == '%' || ft_strchr(STR_CHR_SPECS, *format_i) ||
	ft_strchr(INT_SPECS, *format_i) || ft_strchr(FLOAT_SPECS, *format_i))
	{
		*spec_end = 1;
		g_f->type = *format_i;
		return (1);
	}
	else if (*format_i == 'p')
	{
		*spec_end = 1;
		g_f->type = 'p';
		g_f->curr_flags[3] = 1;
		return (1);
	}
	return (0);
}
