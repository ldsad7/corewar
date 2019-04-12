/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:38:03 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/12 14:30:47 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	free_line_and_exit_main(char *line, t_main *main, int j)
{
	free(line);
	error_exit(e_no_closing_quote, main->num_line, j + 1);
}
