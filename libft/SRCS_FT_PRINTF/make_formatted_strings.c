/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_formatted_strings.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 12:34:27 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:15:10 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	make_str(void)
{
	ft_strchr_wo_zero("di", g_f->type) != 0 ? make_str_di() : 1;
	ft_strchr_wo_zero("bouxX", g_f->type) != 0 ? make_str_boux() : 1;
	ft_strchr_wo_zero("s", g_f->type) != 0 ? make_str_s() : 1;
	ft_strchr_wo_zero("c%", g_f->type) != 0 ? make_str_c() : 1;
	ft_strchr_wo_zero("aAeEfFgG", g_f->type) != 0 ? make_str_aefg() : 1;
	ft_strchr_wo_zero("p", g_f->type) != 0 ? make_str_p() : 1;
	if (!(g_f->type))
		g_f->str = NULL;
}
