/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_p_string_part_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 18:19:34 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:15:59 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fix_prefix_16_p(char **str, int len_ini_tmp_str)
{
	int i;

	if (g_f->curr_flags[3] && (g_f->width_value >
	len_ini_tmp_str + 2 || (*str)[0] == '0'))
	{
		i = -1;
		while ((*str)[++i] == ' ')
			;
		(*str)[++i] = 'x';
		while ((*str)[++i] == '0' || (*str)[i] == 'x')
			(*str)[i] = '0';
	}
}
