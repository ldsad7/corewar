/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_8.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 16:48:42 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/28 01:10:57 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		read_label_indirect(char *line, int *index, t_main **new,
								int *num_args)
{
	int		prev_index;
	char	*tmp;

	prev_index = *index;
	check_for_null(line, index);
	while (line[*index] && !ft_strchr(" \t", line[*index]) &&
	line[*index] != SEPARATOR_CHAR
	&& line[*index] != COMMENT_CHAR && line[*index] != ALT_COMMENT_CHAR)
		(*index)++;
	if (!(tmp = ft_strsub(line, prev_index + 1, *index - prev_index - 1)))
		error_exit(e_malloc_error, g_params->num_line, prev_index + 1 + 1);
	check_valid_label(tmp, prev_index + 1, e_dont_check_in_all_labels);
	free(tmp);
	if (!((*new)->args[(*num_args)++] = ft_strsub(line, prev_index,
													*index - prev_index)))
		error_exit(e_malloc_error, g_params->num_line, prev_index);
}

void		read_number_indirect(char *line, int *index, t_main **new,
								int *num_args)
{
	int		prev_index;

	prev_index = *index;
	if (line[*index] == '-')
		(*index)++;
	if (!(line[*index]) || !ft_strchr("0123456789", line[*index]))
		error_exit(e_incorrect_argument, g_params->num_line, *index + 1);
	while (line[*index] && ft_strchr("0123456789", line[*index]))
		(*index)++;
	if (!((*new)->args[(*num_args)++] = ft_strsub(line, prev_index,
													*index - prev_index)))
		error_exit(e_malloc_error, g_params->num_line, prev_index);
}

void		read_indirect(t_main **new, int *num_args, int *index, char *line)
{
	if (!(g_op_tab[(*new)->num_of_op].args[*num_args] & T_IND))
		error_exit(e_incorrect_argument, g_params->num_line, *index + 1);
	if (line[*index] == LABEL_CHAR)
		read_label_indirect(line, index, new, num_args);
	else
		read_number_indirect(line, index, new, num_args);
	(*new)->size_of_op += 2;
}

void		check_for_null(char *line, int *index)
{
	if (!(line[++(*index)]))
		error_exit(e_incorrect_argument, g_params->num_line, *index + 1);
}

void	reverse_main_list(t_main **list)
{
	t_main *previous;
	t_main *current;
	t_main *next;

	previous = *list;
	if ((current = previous->next) == NULL)
		return ;
	previous->next = NULL;
	while (current->next)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	current->next = previous;
	*list = current;
}
