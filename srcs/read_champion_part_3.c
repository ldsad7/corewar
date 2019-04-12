/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/12 20:51:47 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"


// split function!

char	*comment_filling(char **line, int *j, int fd_input, t_header **header)
{
	char	*comment;
	int		comment_i;
	char	*line_fd;

	comment = name_comment_malloc(COMMENT_LENGTH);
	comment_i = 0;
	while ((*line)[*j] != '"')
	{
		if (!((*line)[*j]) && !(line_fd = NULL) && get_next_line(fd_input, &line_fd) <= 0)
			free_line_and_exit_header(*line, *header, *j);
		else if (!((*line)[*j]))
		{
			*j = 0;
			free(*line);
			*line = line_fd;
			check_length_comment(comment_i, *j, *header);
			(*header)->num_line++;
			comment[comment_i++] = '\n';
			continue ;
		}
		check_length_comment(comment_i, *j, *header);
		comment[comment_i++] = (*line)[(*j)++];
	}
	comment[comment_i] = '\0';
	return (comment);
}

void	check_errors_comment(char *line, int i, int j, t_header *header)
{
	if (!(line[j]))
	{
		if (header->comment)
			error_exit(e_repeating_comment_instruction,
			header->num_line, i + 1);
		else
			error_exit(e_no_comment_after_comment_command,
			header->num_line, j + 1);
	}
	if (line[j] != '"')
		error_exit(e_no_opening_quote, header->num_line, j + 1);
	if (header->comment)
		error_exit(e_repeating_comment_instruction, header->num_line, i + 1);
}

void	parse_comment(char **line, int i, int fd_input, t_header **header)
{
	int		j;

	j = i + ft_strlen(COMMENT_CMD_STRING);
	while ((*line)[j] && ft_strchr(" \n\t", (*line)[j]))
		j++;
	check_errors_comment(*line, i, j, *header);
	++j;
	(*header)->comment = comment_filling(line, &j, fd_input, header);
	j++;
	while ((*line)[j] && ft_strchr(" \n\t", (*line)[j]))
		j++;
	if ((*line)[j] && (*line)[j] != COMMENT_CHAR && (*line)[j] != ALT_COMMENT_CHAR)
		error_exit(e_invalid_instruction, (*header)->num_line, j + 1);
}
