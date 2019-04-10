/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 18:30:21 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:16:46 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*write_nan_inf(double tmp)
{
	if (ft_isnan(tmp) && g_f->big_f == 1)
		return (ft_strdup("NAN"));
	else if (ft_isinf(tmp) == 1 && g_f->big_f == 1)
		return (ft_strdup("INF"));
	else if (ft_isnan(tmp) && g_f->big_f != 1)
		return (ft_strdup("nan"));
	else if (ft_isinf(tmp) == 1 && g_f->big_f != 1)
		return (ft_strdup("inf"));
	else if (ft_isinf(tmp) == -1 && g_f->big_f == 1)
		return (ft_strdup("-INF"));
	return (ft_strdup("-inf"));
}

int			count_decimal_len(char *str)
{
	int i;
	int res;

	i = -1;
	res = 0;
	while (str[++i] && str[i] != '.')
		;
	while (str[++i])
		res++;
	return (res);
}

void		wchar_to_char(char *buffer, int *offset, wchar_t c)
{
	if (c <= 0x7F)
		buffer[(*offset)++] = (char)c;
	else if (c <= 0x7FF)
	{
		buffer[(*offset)++] = 0xC0 | (c >> 6);
		buffer[(*offset)++] = 0x80 | ((c >> 0) & 0x3F);
	}
	else if (c <= 0xFFFF)
	{
		buffer[(*offset)++] = 0xE0 | (c >> 12);
		buffer[(*offset)++] = 0x80 | ((c >> 6) & 0x3F);
		buffer[(*offset)++] = 0x80 | ((c >> 0) & 0x3F);
	}
	else if (c <= 0x1FFFFF)
	{
		buffer[(*offset)++] = 0xF0 | (c >> 18);
		buffer[(*offset)++] = 0x80 | ((c >> 12) & 0x3F);
		buffer[(*offset)++] = 0x80 | ((c >> 6) & 0x3F);
		buffer[(*offset)++] = 0x80 | ((c >> 0) & 0x3F);
	}
	else
		g_count = -1;
}
