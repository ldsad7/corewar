/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/12 20:50:41 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void		parse_instruction(char **line, int i, int fd_input,
								t_header **header)
{
	if (startswith(*line + i, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		parse_name(line, i, fd_input, header);
	else if (startswith(*line + i, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		parse_comment(line, i, fd_input, header);
	else
		error_exit(e_invalid_instruction, (*header)->num_line, i + 1);
}

static void	check_prog_name_and_comment_existence(t_header *header, int i)
{
	if (!(header->prog_name))
		error_exit(e_no_name, header->num_line, i + 1);
	else if (!(header->comment))
		error_exit(e_no_comment, header->num_line, i + 1);
}

static void	parsing_line_by_line_ext(char *line, t_header **header,
									t_main **main)
{
	free(line);
	(*header)->num_line++;
	(*main)->num_line += ((*main)->num_line != 0);
}

static void	parsing_line_by_line(int fd_input, t_header **header,
								t_main **main, char *filename)
{
	char		*line;
	int			i;

	vars_init(header, main, &line, &i);
	while (get_next_line(fd_input, &line) > 0)
	{
		i = 0;
		while (line[i] && ft_strchr(" \t", line[i]))
			i++;
		if (!(line[i]) || line[i] == COMMENT_CHAR ||
			line[i] == ALT_COMMENT_CHAR)
			;
		else if (line[i] == '.')
			parse_instruction(&line, i, fd_input, header);
		else if (!((*header)->prog_name) || !((*header)->comment))
			check_prog_name_and_comment_existence(*header, i);
		else
		{
			if (!((*main)->num_line))
				(*main)->num_line = (*header)->num_line;
			parse_operation(&line, i, fd_input, main);
		}
		parsing_line_by_line_ext(line, header, main);
	}
	check_prog_name_and_comment_existence(*header, i);
	filename = NULL;
}

void		champion_file_parsing(char *filename)
{
	int			fd_input;
	t_header	*header;
	t_main		*main;

	if ((fd_input = open(filename, O_RDONLY)) < 0)
		error_exit(e_open_error, 0, 0);
	if (!(header = (t_header *)malloc(sizeof(t_header))))
		error_exit(e_malloc_error, 0, 0);
	if (!(main = (t_main *)malloc(sizeof(t_main))))
		error_exit(e_malloc_error, 0, 0);
	parsing_line_by_line(fd_input, &header, &main, filename);
	printf("%s\n", header->prog_name);
	printf("%s\n", header->comment);
}
