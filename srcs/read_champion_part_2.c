/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/28 09:55:39 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

char		*name_filling(char **line, int *name_index, int fd_input)
{
	int		name_i;
	char	*name;
	char	*line_fd;

	name = name_comment_malloc(PROG_NAME_LENGTH);
	name_i = 0;
	while ((*line)[*name_index] != '"')
	{
		if (!((*line)[*name_index]) && !(line_fd = NULL) &&
		get_next_line(fd_input, &line_fd) <= 0)
			free_line_and_exit_header(*line, *name_index);
		else if (!((*line)[*name_index]))
		{
			g_params->num_line++;
			check_slash_zero(fd_input, ft_strlen(line_fd) + 1);
			*name_index = 0;
			free(*line);
			*line = line_fd;
			name[name_i++] = '\n';
			check_length_name(name_i, *name_index);
			continue ;
		}
		check_length_name(name_i, *name_index);
		name[name_i++] = (*line)[(*name_index)++];
	}
	name[name_i] = '\0';
	return (name);
}

static void	check_errors_name(char *line, int start_of_name_command,
								int start_of_name, t_header *header)
{
	if (!(line[start_of_name]))
	{
		if (header->prog_name)
			error_exit(e_repeating_name_instruction,
				g_params->num_line, start_of_name_command + 1);
		else
			error_exit(e_no_name_after_name_command,
					g_params->num_line, start_of_name + 1);
	}
	if (header->prog_name)
		error_exit(e_repeating_name_instruction,
				g_params->num_line, start_of_name_command + 1);
	if (line[start_of_name] != '"')
		error_exit(e_no_opening_quote,
			g_params->num_line, start_of_name + 1);
}

/*
**	++name_index after check_errors_name() needed to skip " (opening double quotes sign)
**	++name_index after name_filling() needed to skip " (closing double quotes sign)
*/

void		parse_name(char **line, int start_of_name_command,
						int fd_input, t_header **header)
{
	int		name_index;

	name_index = start_of_name_command + ft_strlen(NAME_CMD_STRING);
	while ((*line)[name_index] && ft_strchr(" \t", (*line)[name_index]))
		name_index++;
	check_errors_name(*line, start_of_name_command, name_index, *header);
	++name_index;
	(*header)->prog_name = name_filling(line, &name_index, fd_input);
	++name_index;
	while ((*line)[name_index] && ft_strchr(" \t", (*line)[name_index]))
		name_index++;
	if ((*line)[name_index] && (*line)[name_index] != COMMENT_CHAR &&
	(*line)[name_index] != ALT_COMMENT_CHAR)
		error_exit(e_invalid_instruction, g_params->num_line, name_index + 1);
}

void	error_no_oper_no_args(char *line, int start_of_op,
						int first_symbol_after_end_of_op)
{
	char *str;

	if (!(str = ft_strsub(line, start_of_op,
	first_symbol_after_end_of_op - start_of_op)))
		error_exit(e_malloc_error, 0, 0);
	if (!find_op(str))
		error_exit(e_no_operation, g_params->num_line, start_of_op + 1);
	else
		error_exit(e_not_enough_arguments, g_params->num_line,
				first_symbol_after_end_of_op + 1);
}

void	check_valid_label(char *str, int pos, int check_in_all_labels)
{
	int		j;
	t_list	*g_labels_tmp;

	j = 0;
	while (str[j])
	{
		if (!ft_strchr(LABEL_CHARS, str[j]))
			error_exit(e_incorrect_symbol_in_label,
			g_params->num_line, pos + j + 1);
		j++;
	}
	g_labels_tmp = g_params->labels_all;
	while (g_labels_tmp && check_in_all_labels)
	{
		if (ft_strequ(g_labels_tmp->content, str))
			error_exit(e_duplicate_label, g_params->num_line, pos);
		g_labels_tmp = g_labels_tmp->next;
	}
}
