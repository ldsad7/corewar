/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format_part_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 18:49:10 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/31 13:59:40 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse_flags(const char *format_i)
{
	int i;

	i = 0;
	while (format_i[i] == '-' || format_i[i] == '+' || format_i[i] == ' ' ||
	format_i[i] == '#' || format_i[i] == '0')
	{
		if (format_i[i] == '-')
			g_f->curr_flags[0] = 1;
		else if (format_i[i] == '+')
			g_f->curr_flags[1] = 1;
		else if (format_i[i] == ' ')
			g_f->curr_flags[2] = 1;
		else if (format_i[i] == '#')
			g_f->curr_flags[3] = 1;
		else if (format_i[i] == '0')
			g_f->curr_flags[4] = 1;
		i++;
	}
	return (i);
}

static void	parsing_loop(char **format)
{
	int i;
	int loop_exit;

	i = 0;
	loop_exit = 0;
	while (!loop_exit)
	{
		i = parse_flags(*format + i);
		i += parse_width(*format + i);
		i += parse_precision(*format + i);
		while (ft_strchr_wo_zero("lhzjtL", *(*format + i)))
			i += parse_size(*format + i);
		i += parse_type(*format + i, &loop_exit);
		i += parse_deprecated(*format + i, &loop_exit);
		if (i == 0)
		{
			g_f->str = make_string_from_char(**format);
			g_f->type = 'c';
			*format += 1;
			break ;
		}
		*format += i;
		i = 0;
	}
	make_str();
}

void		write_ordinary_symbols(char *format, int i, int fd)
{
	if (i > 0)
	{
		g_f->str = ft_strsub(format, 0, i);
		g_count += i;
		write(fd, g_f->str, ft_strlen(g_f->str));
		free(g_f->str);
		g_f->str = NULL;
	}
}

static void	f_null_c_len(void)
{
	g_count += g_f->null_c_len;
	g_f->null_c_len = (g_f->null_c_len == 0) ? 1 : g_f->null_c_len;
	write(1, g_f->str, g_f->null_c_len);
}

void		parse_print_format(char *format, int i, int fd)
{
	while (*(format + i))
	{
		if (*(format + i) == '%')
		{
			write_ordinary_symbols(format, i, fd);
			format += i + 1;
			i = -1;
			parsing_loop(&format);
			if (!(g_f->str) || g_count < 0)
				return ;
			if (g_f->null_c_len == -1)
			{
				g_count += ft_strlen(g_f->str);
				write(fd, g_f->str, ft_strlen(g_f->str));
			}
			else
				f_null_c_len();
			clear_all_exit(0);
			g_f = g_f_new();
		}
		else
			format = check_colors(format, &i, fd);
		i++;
	}
	write_ordinary_symbols(format, i, fd);
}
