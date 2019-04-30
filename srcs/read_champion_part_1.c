/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/30 00:57:41 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		parse_instruction(char **line, int i, int fd_input,
								t_header **header)
{
	if (startswith(*line + i, NAME_CMD_STRING))
		parse_name(line, i, fd_input, header);
	else if (startswith(*line + i, COMMENT_CMD_STRING))
		parse_comment(line, i, fd_input, header);
}

static void	check_prog_name_and_comment_existence(t_header *header, int i)
{
	if (!(header->prog_name))
		error_exit(e_no_name, g_params->num_line, i + 1);
	else if (!(header->comment))
		error_exit(e_no_comment, g_params->num_line, i + 1);
}

static void	parsing_line_by_line_ext(char *line)
{
	free(line);
	g_params->num_line++;
}

static void	parsing_line_by_line(int fd_input, t_header **header,
								t_main **main)
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
		{
			if (!((*header)->prog_name) || !((*header)->comment))
				check_slash_zero(fd_input, ft_strlen(line) + 1);
			else if (check_slash_zero_and_exit(fd_input, ft_strlen(line) + 1, *main))
				break ;
		}
		else
		{
			if (startswith(line + i, NAME_CMD_STRING)
					|| startswith(line + i, COMMENT_CMD_STRING))
				parse_instruction(&line, i, fd_input, header);
			else if (!((*header)->prog_name) || !((*header)->comment))
				check_prog_name_and_comment_existence(*header, i);
			else
				parse_operation(&line, i, fd_input, main);
			if (check_slash_zero_and_exit(fd_input, ft_strlen(line) + 1, *main))
				break ;
		}
		parsing_line_by_line_ext(line);
	}
	free(line);
	check_prog_name_and_comment_existence(*header, i);
}



// void		free_header(t_header *header)
// {
// 	free(header->comment);
// 	free(header->prog_name);
// 	free(header);
// }

void		champion_file_parsing(char *filename, int annotated_version)
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
	parsing_line_by_line(fd_input, &header, &main);
	close(fd_input);
	if (main->num_of_op == -1)
		error_exit(e_no_exec_code, g_params->num_line, 0);
	reverse_main_list(&main);
	// print_main(main);
	replace_labels_with_numbers(&main);
	if (annotated_version)
		dump_champion(header, main);
	else
		translate_to_byte_code(header, main, filename);
	exit(0);
	// free_main(main);
	// free_header(header);
}
