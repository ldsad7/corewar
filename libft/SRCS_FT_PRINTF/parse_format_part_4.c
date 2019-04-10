/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format_part_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 18:49:10 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/31 13:58:08 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	apply_text_edit2(char *format, int j, int ord, int fd)
{
	write_ordinary_symbols(format, ord, fd);
	if (ft_strstr(ft_strsub(format, 0, j + 1), "{BOLD}"))
		write(1, BC_BOLD, ft_strlen(BC_BOLD));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{N_BOLD}"))
		write(1, BC_NBOLD, ft_strlen(BC_NBOLD));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{UNDERLINE}"))
		write(1, BC_UNDERLINE, ft_strlen(BC_UNDERLINE));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{N_UNDERLINE}"))
		write(1, BC_NUNDERLINE, ft_strlen(BC_NUNDERLINE));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{INVERSE}"))
		write(1, BC_INVERSE, ft_strlen(BC_INVERSE));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{N_INVERSE}"))
		write(1, BC_NINVERSE, ft_strlen(BC_NINVERSE));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{BLINK}"))
		write(1, BC_BLINK, ft_strlen(BC_BLINK));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{N_BLINK}"))
		write(1, BC_NBLINK, ft_strlen(BC_NBLINK));
}

int			apply_text_edit(char *format, int j, int ord, int fd)
{
	if (ft_strstr(ft_strsub(format, 0, j + 1), "{BOLD}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{N_BOLD}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{UNDERLINE}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{N_UNDERLINE}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{INVERSE}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{N_INVERSE}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{BLINK}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{N_BLINK}"))
	{
		apply_text_edit2(format, j, ord, fd);
		return (1);
	}
	return (0);
}

char		*check_colors(char *format, int *i, int fd)
{
	char *format_ini;

	if (*(format + *i) == '{')
	{
		format_ini = ft_strdup(format);
		format = parse_colors(format, *i, fd);
		if (ft_strcmp(format_ini, format))
			*i = -1;
		free(format_ini);
	}
	return (format);
}

int			parse_deprecated(const char *format_i, int *spec_end)
{
	if (ft_strchr_wo_zero("DOUCSF", *format_i))
	{
		if (*format_i == 'D')
			g_f->type = 'd';
		else if (*format_i == 'O')
			g_f->type = 'o';
		else if (*format_i == 'U')
			g_f->type = 'u';
		else if (*format_i == 'C')
			g_f->type = 'c';
		else if (*format_i == 'S')
			g_f->type = 's';
		else if (*format_i == 'F')
			g_f->type = 'f';
		if (*format_i != 'F')
			g_f->size = L_L;
		else
			g_f->big_f = 1;
		*spec_end = 1;
		return (1);
	}
	return (0);
}
