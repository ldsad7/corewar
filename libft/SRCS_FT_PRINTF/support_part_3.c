/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 18:30:21 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:16:49 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		wchar_strlen(wchar_t *str)
{
	int res;

	res = 0;
	while (*str)
	{
		if (*str <= 0x7F)
			res += 1;
		else if (*str <= 0x7FF)
			res += 2;
		else if (*str <= 0xFFFF)
			res += 3;
		else if (*str <= 0x1FFFFF)
			res += 4;
		str++;
	}
	return (res);
}

int		wint_size(wint_t c)
{
	int res;

	res = 0;
	if (c <= 0x7F)
		res += 1;
	else if (c <= 0x7FF)
		res += 2;
	else if (c <= 0xFFFF)
		res += 3;
	else if (c <= 0x1FFFFF)
		res += 4;
	return (res);
}

int		wchar_strlen_symbols(wchar_t *str)
{
	int res;

	res = 0;
	while (*str)
	{
		res += 1;
		str++;
	}
	return (res);
}

void	upper_lower_xp(char **str)
{
	int i;

	i = -1;
	if (g_f->type == 'x' || g_f->type == 'p')
		while ((*str)[++i])
			(*str)[i] = ft_tolower((*str)[i]);
}

char	*make_string_from_char(char c)
{
	char *res;

	if (!(res = ft_strnew(1)))
		clear_all_exit(-1);
	res[0] = c;
	return (res);
}
