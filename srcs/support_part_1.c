/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:38:03 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/12 20:44:09 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	error_exit3(int value, int num_line, int symbol)
{
	if (value == e_no_comment)
		exit(ft_fprintf(2,
"Error: no comment or comment goes after the first operation [%d:%d]\n",
						num_line, symbol));
	else if (value == e_empty_label)
		exit(ft_fprintf(2, "Error: empty label of operation [%d:%d]\n",
						num_line, symbol));
	else if (value == e_no_operation)
		exit(ft_fprintf(2, "Error: there is no such operation [%d:%d]\n",
						num_line, symbol));
	else if (value == e_not_enough_arguments)
		exit(ft_fprintf(2, "Error: there is not enough arguments [%d:%d]\n",
						num_line, symbol));
	else if (value == e_incorrect_symbol_in_label)
		exit(ft_fprintf(2, "Error: incorrect symbol in label [%d:%d]\n",
						num_line, symbol));
	// else if (value == e_empty_file)
	// 	exit(ft_fprintf(2, "Error: file is empty\n"));
	// else if (value == e_error_reading_file)
	// 	exit(ft_fprintf(2, "Error: reading file failed\n"));
	// else if (value == e_last_instruction_not_slash_n)
	// 	exit(ft_fprintf(2, "Error: last instruction has no \\n\n"));
}

static void	error_exit2(int value, int num_line, int symbol)
{
	if (value == e_no_comment_after_comment_command)
		exit(ft_fprintf(2,
"Error: no comment after .comment instruction [%d:%d]\n",
						num_line, symbol));
	else if (value == e_no_opening_quote)
		exit(ft_fprintf(2, "Error: no opening \" after instruction [%d:%d]\n",
						num_line, symbol));
	else if (value == e_no_closing_quote)
		exit(ft_fprintf(2, "Error: no closing \" after instruction [%d:%d]\n",
						num_line, symbol));
	else if (value == e_name_too_long)
		exit(ft_fprintf(2, "Error: program name is too long [%d:%d]\n",
						num_line, symbol));
	else if (value == e_comment_too_long)
		exit(ft_fprintf(2, "Error: comment is too long [%d:%d]\n",
						num_line, symbol));
	else if (value == e_no_name)
		exit(ft_fprintf(2,
"Error: no name or name goes after the first operation [%d:%d]\n",
						num_line, symbol));
	error_exit3(value, num_line, symbol);	
}

void		error_exit(int value, int num_line, int symbol)
{
	if (value == e_num_args_not_one)
		exit(ft_fprintf(2, "Error: number of given arguments is not one\n"));
	else if (value == e_incorrect_s_file)
		exit(ft_fprintf(2, "Error: given file hasn't .s extension\n"));
	else if (value == e_open_error)
		exit(ft_fprintf(2, "Error: attempting to open file failed\n"));
	else if (value == e_malloc_error)
		exit(ft_fprintf(2, "Error: Malloc returned NULL\n"));
	else if (value == e_invalid_instruction)
		exit(ft_fprintf(2, "Error: there is no such instruction [%d:%d]\n",
						num_line, symbol));
	else if (value == e_repeating_name_instruction)
		exit(ft_fprintf(2,
"Error: .name instruction repeated at least twice [%d:%d]\n",
						num_line, symbol));
	else if (value == e_repeating_comment_instruction)
		exit(ft_fprintf(2,
"Error: .comment instruction repeated at least twice [%d:%d]\n",
						num_line, symbol));
	else if (value == e_no_name_after_name_command)
		exit(ft_fprintf(2, "Error: no name after .name instruction [%d:%d]\n",
						num_line, symbol));
	error_exit2(value, num_line, symbol);
}

void		vars_init(t_header **header, t_main **main, char **line, int *i)
{
	*i = 0;
	*line = NULL;
	(*header)->magic = 0; // NB: заменить
	(*header)->prog_name = NULL;
	(*header)->prog_size = 0;
	(*header)->comment = NULL;
	(*header)->num_line = 1;
	(*main)->num_of_op = 0;
	(*main)->size_of_op = 0;
	(*main)->label = NULL;
	(*main)->next = NULL;
	(*main)->num_line = 0;
	(*main)->args[0] = 0;
	(*main)->args[1] = 0;
	(*main)->args[2] = 0;
}

void	free_line_and_exit_header(char *line, t_header *header, int j)
{
	free(line);
	error_exit(e_no_closing_quote, header->num_line, j + 1);
}
