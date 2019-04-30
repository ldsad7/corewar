/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/28 08:53:51 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

char	*comment_filling(char **line, int *comment_index, int fd_input)
{
	char	*comment;
	int		comment_i;
	char	*line_fd;

	comment = name_comment_malloc(COMMENT_LENGTH);
	comment_i = 0;
	while ((*line)[*comment_index] != '"')
	{
		if (!((*line)[*comment_index]) && !(line_fd = NULL)
			&& get_next_line(fd_input, &line_fd) <= 0)
			free_line_and_exit_header(*line, *comment_index);
		else if (!((*line)[*comment_index]))
		{
			*comment_index = 0;
			check_slash_zero(fd_input, ft_strlen(line_fd) + 1);
			free(*line);
			*line = line_fd;
			g_params->num_line++;
			comment[comment_i++] = '\n';
			check_length_comment(comment_i, *comment_index);
			continue ;
		}
		check_length_comment(comment_i, *comment_index);
		comment[comment_i++] = (*line)[(*comment_index)++];
	}
	comment[comment_i] = '\0';
	return (comment);
}

void	check_errors_comment(char *line, int start_of_comment_command,
								int start_of_comment, t_header *header)
{
	if (!(line[start_of_comment]))
	{
		if (header->comment)
			error_exit(e_repeating_comment_instruction,
			g_params->num_line, start_of_comment_command + 1);
		else
			error_exit(e_no_comment_after_comment_command,
			g_params->num_line, start_of_comment + 1);
	}
	if (header->comment)
		error_exit(e_repeating_comment_instruction, g_params->num_line,
					start_of_comment_command + 1);
	if (line[start_of_comment] != '"')
		error_exit(e_no_opening_quote, g_params->num_line,
					start_of_comment + 1);
}

void	parse_comment(char **line, int start_of_comment_command,
						int fd_input, t_header **header)
{
	int		comment_index;

	comment_index = start_of_comment_command + ft_strlen(COMMENT_CMD_STRING);
	while ((*line)[comment_index] && ft_strchr(" \t", (*line)[comment_index]))
		comment_index++;
	check_errors_comment(*line, start_of_comment_command, comment_index, *header);
	++comment_index;
	(*header)->comment = comment_filling(line, &comment_index, fd_input);
	++comment_index;
	while ((*line)[comment_index] && ft_strchr(" \t", (*line)[comment_index]))
		++comment_index;
	if ((*line)[comment_index] && (*line)[comment_index] != COMMENT_CHAR
		&& (*line)[comment_index] != ALT_COMMENT_CHAR)
		error_exit(e_invalid_instruction, g_params->num_line,
					comment_index + 1);
}

t_main	*new_op_setup(t_main **main)
{
	t_main	*new;

	if (((*main)->size_of_op))
	{
		if (!(new = (t_main *)malloc(sizeof(t_main))))
			error_exit(e_malloc_error, 0, 0);
		new->num_of_op = 0;
		new->size_of_op = 0;
		new->labels = NULL;
		new->next = NULL;
		new->args[0] = 0;
		new->args[1] = 0;
		new->args[2] = 0;
	}
	else
		new = *main;
	return (new);
}

int		check_after_label(char **line, t_indexes *indexes)
{
	int		i;

	i = indexes->label_or_op_end;
	while ((*line)[++i] && ft_strchr(" \t", (*line)[i]))
		;
	if ((*line)[i] == COMMENT_CHAR || (*line)[i] == ALT_COMMENT_CHAR ||
	!(*line)[i])
	{
		indexes->launch_gnl = 1;
		return (0);
	}
	else if (!ft_strchr(ALPHABET, (*line)[i]))
		error_exit(e_no_operation, g_params->num_line, i);
	indexes->label_or_op_start = i;
	return (1);
}
