/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format_part_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 18:49:10 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/31 13:55:08 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	apply_colors2(char *format, int j, int ord, int fd)
{
	write_ordinary_symbols(format, ord, fd);
	if (ft_strstr(ft_strsub(format, 0, j + 1), "{red}"))
		write(1, BC_RED, ft_strlen(BC_RED));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{green}"))
		write(1, BC_GREEN, ft_strlen(BC_GREEN));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{cyan}"))
		write(1, BC_CYAN, ft_strlen(BC_CYAN));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{black}"))
		write(1, BC_BLACK, ft_strlen(BC_BLACK));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{gray}"))
		write(1, BC_GRAY, ft_strlen(BC_GRAY));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{blue}"))
		write(1, BC_BLUE, ft_strlen(BC_BLUE));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{magenta}"))
		write(1, BC_MAGENTA, ft_strlen(BC_MAGENTA));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{yellow}"))
		write(1, BC_YELLOW, ft_strlen(BC_YELLOW));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{def}"))
		write(1, BC_DEFAULT, ft_strlen(BC_DEFAULT));
}

static int	apply_colors(char *format, int j, int ord, int fd)
{
	if (ft_strstr(ft_strsub(format, 0, j + 1), "{red}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{green}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{yellow}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{blue}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{magenta}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{black}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{cyan}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{gray}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{def}"))
	{
		apply_colors2(format, j, ord, fd);
		return (1);
	}
	return (0);
}

static void	apply_bg_colors2(char *format, int j, int ord, int fd)
{
	write_ordinary_symbols(format, ord, fd);
	if (ft_strstr(ft_strsub(format, 0, j + 1), "{BG_RED}"))
		write(1, BC_BG_RED, ft_strlen(BC_RED));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{BG_BLACK}"))
		write(1, BC_BG_BLACK, ft_strlen(BC_BG_BLACK));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{BG_GREEN}"))
		write(1, BC_BG_GREEN, ft_strlen(BC_BG_GREEN));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{BG_BROWN}"))
		write(1, BC_BG_BROWN, ft_strlen(BC_BG_BROWN));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{BG_BLUE}"))
		write(1, BC_BG_BLUE, ft_strlen(BC_BG_BLUE));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{BG_MAGENTA}"))
		write(1, BC_BG_MAGENTA, ft_strlen(BC_BG_MAGENTA));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{BG_CYAN}"))
		write(1, BC_BG_CYAN, ft_strlen(BC_BG_CYAN));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{BG_GRAY}"))
		write(1, BC_BG_GRAY, ft_strlen(BC_BG_GRAY));
	else if (ft_strstr(ft_strsub(format, 0, j + 1), "{BG_DEF}"))
		write(1, BC_DEFAULT, ft_strlen(BC_DEFAULT));
}

static int	apply_bg_colors(char *format, int j, int ord, int fd)
{
	if (ft_strstr(ft_strsub(format, 0, j + 1), "{BG_RED}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{BG_BLACK}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{BG_GREEN}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{BG_BROWN}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{BG_BLUE}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{BG_MAGENTA}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{BG_CYAN}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{BG_GRAY}") ||
	ft_strstr(ft_strsub(format, 0, j + 1), "{BG_DEF}"))
	{
		apply_bg_colors2(format, j, ord, fd);
		return (1);
	}
	return (0);
}

char		*parse_colors(char *format, int ord, int fd)
{
	int j;
	int found_close_bracket;

	j = ord - 1;
	found_close_bracket = 0;
	while (format[++j])
		if (format[j] == '}')
		{
			found_close_bracket = 1;
			break ;
		}
	if (found_close_bracket)
	{
		if (apply_colors(format, j, ord, fd))
			return (format + j + 1);
		if (apply_bg_colors(format, j, ord, fd))
			return (format + j + 1);
		if (apply_text_edit(format, j, ord, fd))
			return (format + j + 1);
	}
	return (format);
}
