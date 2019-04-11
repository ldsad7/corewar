/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:38:03 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/11 15:19:51 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	error_exit(int value)
{
	if (value == e_num_args_not_one)
		exit(ft_fprintf(2, "Error: number of given arguments is not one\n"));
	else if (value == e_incorrect_file)
		exit(ft_fprintf(2, "Error: incorrect file argument\n"));
	else if (value == e_open_error)
		exit(ft_fprintf(2, "Error: attempting to open file failed\n"));
	else if (value == e_malloc_error)
		exit(ft_fprintf(2, "Error: Malloc returned NULL\n"));
	else if (value == e_empty_file)
		exit(ft_fprintf(2, "Error: file is empty\n"));
	else if (value == e_error_reading_file)
		exit(ft_fprintf(2, "Error: reading file failed\n"));
	else if (value == e_last_instruction_not_slash_n)
		exit(ft_fprintf(2, "Error: last instruction has no \\n\n"));
}
