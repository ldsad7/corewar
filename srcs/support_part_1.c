/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:38:03 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/30 02:58:39 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

static void	error_exit5(int value, int num_line, int symbol)
{
	if (value == e_cor_file_is_too_short)
		exit(ft_fprintf(2, "Error: .cor file is too short [%d:%d]\n",
						num_line, symbol));
	else if (value == e_incorrect_null_sequence)
		exit(ft_fprintf(2,
"Error: incorrect null sequence in .cor file [%d:%d]\n", num_line, symbol));
	else if (value == e_exec_code_size_is_too_big)
		exit(ft_fprintf(2,
"Error: exec code size in .cor file is too big [%d:%d]\n", num_line, symbol));
	else if (value == e_incorrect_operation_number)
		exit(ft_fprintf(2,
"Error: incorrect operation number in .cor file [%d:%d]\n", num_line, symbol));
	else if (value == e_bad_argument_in_flag_n)
		exit(ft_fprintf(2,
"Error: bad argument in flag n (maybe duplicated bot number)\n"));
	else if (value == e_incorrect_argument_after_dump_flag)
		exit(ft_fprintf(2, "Error: bad argument in flag dump\n"));
	else if (value == e_too_much_bots)
		exit(ft_fprintf(2, "Error: too much bots\n"));
	else if (value == e_inconsistent_bot_order)
		exit(ft_fprintf(2, "Error: inconsistent bots' order\n"));
	error_exit6(value, num_line, symbol);
}

static void	error_exit4(int value, int num_line, int symbol)
{
	if (value == e_two_labels_in_row)
		exit(ft_fprintf(2, "Error: two labels in row [%d:%d]\n",
						num_line, symbol));
	else if (value == e_lseek_error)
		exit(ft_fprintf(2, "Error: lseek error [%d:%d]\n",
						num_line, symbol));
	else if (value == e_instruction_not_slash_n)
		exit(ft_fprintf(2, "Error: \\0 is forbidden here [%d:%d]\n",
						num_line, symbol));
	else if (value == e_incorrect_cor_file)
		exit(ft_fprintf(2, "Error: given file hasn't .cor extension\n"));
	else if (value == e_no_label)
		exit(ft_fprintf(2, "Error: there is no such label [%d:%d]\n",
						num_line, symbol));
	else if (value == e_exec_code_size_too_big)
		exit(ft_fprintf(2,
"Error: exec code size is too big (bigger than unsigned int)\n"));
	else if (value == e_incorrect_flag)
		exit(ft_fprintf(2, "Error: unknown flag is given\n"));
	else if (value == e_incorrect_magic_header)
		exit(ft_fprintf(2,
"Error: incorrect magic header in .cor file [%d:%d]\n",
						num_line, symbol));
	error_exit5(value, num_line, symbol);
}

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
	else if (value == e_too_many_arguments)
		exit(ft_fprintf(2, "Error: redundant argument [%d:%d]\n",
						num_line, symbol));
	else if (value == e_duplicate_label)
		exit(ft_fprintf(2, "Error: duplicate label [%d:%d]\n",
						num_line, symbol));
	error_exit4(value, num_line, symbol);
}

static void	error_exit2(int value, int num_line, int symbol)
{
	if (value == e_no_comment_after_comment_command)
		exit(ft_fprintf(2,
"Error: no comment after .comment instruction [%d:%d]\n",
						num_line, symbol));
	else if (value == e_comment_too_long)
		exit(ft_fprintf(2, "Error: comment is too long [%d:%d]\n",
						num_line, symbol));
	else if (value == e_no_name)
		exit(ft_fprintf(2,
"Error: no name or name goes after the first operation [%d:%d]\n",
						num_line, symbol));
	else if (value == e_invalid_instruction)
		exit(ft_fprintf(2, "Error: there is no such instruction [%d:%d]\n",
						num_line, symbol));
	else if (value == e_incorrect_argument)
		exit(ft_fprintf(2, "Error: incorrect argument [%d:%d]\n",
						num_line, symbol));
	else if (value == e_no_separator)
		exit(ft_fprintf(2,
"Error: no separator '%c' between arguments [%d:%d]\n",
SEPARATOR_CHAR, num_line, symbol));
	else if (value == e_mismatched_sizes)
		exit(ft_fprintf(2,
"Error: given size of exec code and actual size of exec code do not match\n"));
	error_exit3(value, num_line, symbol);
}

void		error_exit(int value, int num_line, int symbol)
{
	if (value == e_num_args_not_one_or_two)
	{
		ft_fprintf(2, "Error: number of given arguments is not one or two\n");
		exit(ft_printf("Usage: ./asm [-a] <sourcefile.s> | -disass \
<sourcefile.cor>\n\t-a : Instead of creating a .cor file, outputs a stripped \
and annotated version of the code to the standard output\n\t-disass : \
disassemble byte code to assembler code and output to the standard output\n"));
	}
	else if (value == e_incorrect_s_file)
		exit(ft_fprintf(2, "Error: given file hasn't .s extension\n"));
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
	else if (value == e_no_operation_after_label)
		exit(ft_fprintf(2, "Error: there is no operation after label [%d:%d]\n",
						num_line, symbol));
	error_exit2(value, num_line, symbol);
}

