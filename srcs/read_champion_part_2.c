/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/12 16:48:44 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"



// split function!

char		*name_filling(char **line, int *j, int fd_input, t_header **header)
{
	int		name_i;
	char	*name;
	char	*line_fd;

	name = name_comment_malloc(PROG_NAME_LENGTH);
	name_i = 0;
	while ((*line)[*j] != '"')
	{
		if (!((*line)[*j]) && !(line_fd = NULL) &&
		get_next_line(fd_input, &line_fd) <= 0)
			free_line_and_exit_header(*line, *header, *j);
		else if (!((*line)[*j]))
		{
			*j = 0;
			free(*line);
			*line = line_fd;
			check_length_name(name_i, *j, *header);
			(*header)->num_line++;
			name[name_i++] = '\n';
			continue ;
		}
		check_length_name(name_i, *j, *header);
		name[name_i++] = (*line)[(*j)++];
	}
	name[name_i] = '\0';
	return (name);
}

static void	check_errors_name(char *line, int i, int j, t_header *header)
{
	if (!(line[j]))
	{
		if (header->prog_name)
			error_exit(e_repeating_name_instruction, header->num_line, i + 1);
		else
			error_exit(e_no_name_after_name_command, header->num_line, j + 1);
	}
	if (line[j] != '"')
		error_exit(e_no_opening_quote, header->num_line, j + 1);
	if (header->prog_name)
		error_exit(e_repeating_name_instruction, header->num_line, i + 1);
}

/*
**	++j after check_errors_name() needed to skip " (opening double quotes sign)
**	j++ after name_filling() needed to skip " (closing double quotes sign)
*/

void		parse_name(char **line, int i, int fd_input, t_header **header)
{
	int		j;

	j = i + 5;
	while ((*line)[j] && ft_strchr(" \n\t", (*line)[j]))
		j++;
	check_errors_name(*line, i, j, *header);
	++j;
	(*header)->prog_name = name_filling(line, &j, fd_input, header);
	j++;
	while ((*line)[j] && ft_strchr(" \n\t", (*line)[j]))
		j++;
	if ((*line)[j] && (*line)[j] != COMMENT_CHAR &&
	(*line)[j] != ALT_COMMENT_CHAR)
		error_exit(e_invalid_instruction, (*header)->num_line, j + 1);
}
