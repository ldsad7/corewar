/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:38:03 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/11 13:57:12 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	error_exit(int value)
{
	if (value == e_num_args_not_one)
		exit(ft_fprintf(2, "Number of given arguments is not one\n"));
	else if (value == e_incorrect_file)
		exit(ft_fprintf(2, "Incorrect file argument\n"));
	else if (value == e_open_error)
		exit(ft_fprintf(2, "Error attempting to open file\n"));
	else if (value == e_malloc_error)
		exit(ft_fprintf(2, "Malloc error\n"));
	else if (value == e_empty_file)
		exit(ft_fprintf(2, "File is empty\n"));
	else if (value == e_error_reading_file)
		exit(ft_fprintf(2, "Error when reading file\n"));
}
