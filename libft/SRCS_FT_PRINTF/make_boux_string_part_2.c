/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_boux_string_part_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:42:35 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:15:02 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	function_for_zero_in_octal_spec(char **str)
{
	if (g_f->prec_value == -1 || (g_f->curr_flags[3] && ft_strlen(*str) < 2))
	{
		free(*str);
		*str = ft_strdup("0");
		return ('o');
	}
	return (0);
}

static void	apply_prefix_octal(char **res, char **str)
{
	if (!(*res = ft_strnew(ft_strlen(*str) + 1)))
		clear_all_exit(-1);
	(*res)[0] = '0';
	ft_strcat(*res, *str);
	free(*str);
	*str = *res;
}

static void	apply_prefix_binary_hex(char **res, char **str, char num_sys)
{
	if (!(*res = ft_strnew(ft_strlen(*str) + 2)))
		clear_all_exit(-1);
	(*res)[1] = num_sys;
	(*res)[0] = '0';
	ft_strcat(*res, *str);
	free(*str);
	*str = *res;
}

char		apply_prefix_boux(char **str, unsigned long long tmp)
{
	char	*res;
	char	num_sys;

	num_sys = '\0';
	if (g_f->curr_flags[3] && tmp != 0)
	{
		res = NULL;
		ft_strchr("b", g_f->type) ? num_sys = 'b' : 1;
		ft_strchr("xX", g_f->type) ? num_sys = 'X' : 1;
		if (g_f->type == 'o' && (*str)[0] != '0')
			apply_prefix_octal(&res, str);
		else if (ft_strchr("bxX", g_f->type))
			apply_prefix_binary_hex(&res, str, num_sys);
		return (num_sys);
	}
	else if (tmp == 0 && g_f->type == 'o')
		return (function_for_zero_in_octal_spec(str));
	return (0);
}

void		apply_zero_boux(char **str)
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
