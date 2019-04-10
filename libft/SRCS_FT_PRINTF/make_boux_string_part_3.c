/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_boux_string_part_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:42:35 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:14:58 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		fix_prefix_2_16_boux(char **str, char num_sys, int len_ini_tmp_str)
{
	int i;

	if (g_f->curr_flags[3] && (g_f->width_value >
	len_ini_tmp_str + 2 || (*str)[0] == '0') && (g_f->type == 'b' ||
	g_f->type == 'x' || g_f->type == 'X') && num_sys != '\0')
	{
		i = -1;
		while ((*str)[++i] == ' ')
			;
		(*str)[++i] = num_sys;
		while ((*str)[++i] == '0' || (*str)[i] == num_sys)
			(*str)[i] = '0';
	}
}
