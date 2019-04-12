/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/12 20:09:29 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static t_main	*new_op_setup(t_main **main, int i)
{
	t_main	*new;

	if (((*main)->num_of_op))
	{
		if (!(new = (t_main *)malloc(sizeof(t_main))))
			error_exit(e_malloc_error, (*main)->num_line, i);
		new->num_line = (*main)->num_line;
	}
	else
		new = *main;
	return (new);
}
//this one can be applied to read_command()
void	error_no_oper_no_args(char **line, int i, int j, t_main **main)
{
	if (!find_op(ft_strsub(*line, i, j - i)))
		error_exit(e_no_operation, (*main)->num_line, i);
	else
		error_exit(e_not_enough_arguments, (*main)->num_line, j);
}

void	check_label(char *str, int i, t_main *main)
{
	int		j;

	j = 0;
	while (str[j])
	{
		if (!ft_strchr(LABEL_CHARS, str[j]))
			error_exit(e_incorrect_symbol_in_label, main->num_line, i + j);
		j++;
	}
}



/*
**	row 72 - if found operation AND !((*line)[j]) -> exit with error
**	row 65 - else needed only once - when main struct is created outside
**	 of this function
*/

void	parse_operation(char **line, int i, int fd_input, t_main **main)
{
	t_main	*new;
	int		j;
	char	*tmp;

	new = new_op_setup(main, i);
	j = i;
	if ((*line)[j] == LABEL_CHAR)
		error_exit(e_empty_label, (*main)->num_line, i);
	while ((*line)[j] && !ft_strchr(" \t", (*line)[j]) &&
	(*line)[j] != LABEL_CHAR)
		j++;
	if (!((*line)[j]))
		error_no_oper_no_args(line, i, j, main);
	else if ((*line)[j] == LABEL_CHAR)
	{
		if (!(new->label = ft_strsub(*line, i, j - i)))
			error_exit(e_malloc_error, (*main)->num_line, j);
		check_label(new->label, i, *main);
		j++;
		read_command(line, &j, fd_input, &new);
	}
	else if (!ft_strchr(" \t", (*line)[j]))
	{
		new->label = NULL;
		if (!(tmp = ft_strsub(*line, i, j - i)))
			error_exit(e_malloc_error, (*main)->num_line, i);
		if (!(new->num_of_op = find_op(tmp)))
			error_exit(e_no_operation, (*main)->num_line, j);
		free(tmp);
		// read_arguments(line, &j, &new);
	}
	if (new == *main)
		new->next = NULL;
	else
		new->next = *main;
	*main = new;
}
