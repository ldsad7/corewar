/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 00:55:36 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/30 00:58:52 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <string.h>

typedef struct					s_header
{
	char						*prog_name;
	char						*comment;
}								t_header;

typedef struct					s_main
{
	t_list						*labels;
	int							num_of_op;
	int							size_of_op;
	char						*args[3];
	char						*old_args[3];
	int							args_row_num;
	int							args_symbols_nums[3];
	struct s_main				*next;
}								t_main;

typedef struct					s_op
{
	char						*name;
	int							num_of_args;
	int							args[3];
	int							num;
	int							cycles_before_execution;
	int							arg_type_code;
	int							size_of_t_dir;
	int							changes_carry;
}								t_op;

typedef struct					s_indexes
{
	int							label_or_op_start;
	int							label_or_op_end;
	int							quit;
	int							launch_gnl;
}								t_indexes;

typedef struct					s_params
{
	t_list						*labels_all;
	int							num_line;
}								t_params;

# define NUM_OF_OPS				16

extern t_op						g_op_tab[NUM_OF_OPS];
extern t_params					*g_params;

enum {
	e_num_args_not_one_or_two,
	e_incorrect_s_file,
	e_open_error,
	e_malloc_error,
	e_repeating_name_instruction,
	e_repeating_comment_instruction,
	e_no_name_after_name_command,
	e_no_comment_after_comment_command,
	e_no_opening_quote,
	e_no_closing_quote,
	e_name_too_long,
	e_comment_too_long,
	e_no_name,
	e_no_comment,
	e_empty_label,
	e_no_operation,
	e_not_enough_arguments,
	e_incorrect_symbol_in_label,
	e_invalid_instruction,
	e_no_operation_after_label,
	e_incorrect_argument,
	e_no_separator,
	e_too_many_arguments,
	e_duplicate_label,
	e_lseek_error,
	e_instruction_not_slash_n,
	e_two_labels_in_row,
	e_incorrect_cor_file,
	e_no_label,
	e_exec_code_size_too_big,
	e_incorrect_flag,
	e_incorrect_magic_header,
	e_cor_file_is_too_short,
	e_incorrect_null_sequence,
	e_exec_code_size_is_too_big,
	e_incorrect_operation_number,
	e_mismatched_sizes,
	e_bad_argument_in_flag_n,
	e_incorrect_argument_after_dump_flag,
	e_too_much_bots,
	e_inconsistent_bot_order,
	e_no_arguments_for_corewar,
	e_no_exec_code
};

enum {
	e_dont_check_in_all_labels,
	e_check_in_all_labels
};

void							error_exit(int value, int num_line, int symbol);
void							g_params_init(void);
void							vars_init(t_header **header, t_main **main,
								char **line, int *i);
void							champion_file_parsing(char *filename,
								int annotated_version);
int								startswith(char *str, char *start);
int								endswith(char *str, char *end);
void							parse_name(char **line, int i, int fd_input,
								t_header **header);
void							parse_comment(char **line, int i, int fd_input,
								t_header **header);
char							*name_comment_malloc(int len);
void							free_line_and_exit_header(char *line, int j);
void							free_line_and_exit_main(char *line, int j);
void							parse_operation(char **line,
								int label_or_op_start, int fd_input,
								t_main **main);
void							check_length_name(int name_i, int j);
void							check_length_comment(int comment_i, int j);
void							read_command(char **line, int j,
								int fd_input, t_main **new);
int								find_op(char *str);
void							error_no_oper_no_args(char *line, int i, int j);
void							update_main(t_main **main, t_main **new);
void							check_op(t_main *new, int label_or_op_start,
								int index, char *line);
void							read_arguments(char *line, int index,
								t_main **new, int fd_input);
void							check_valid_label(char *str, int pos,
								int check_in_all_labels);
void							read_direct(t_main **new, int *num_args,
								int *index, char *line);
void							read_indirect(t_main **new, int *num_args,
								int *index, char *line);
void							check_for_null(char *line, int *index);
void							print_main(t_main *main);
void							reverse_main_list(t_main **list);
void							add_label_to_labels_arr(char *label,
								char **labels_arr);
int								check_label_in_labels_arr(char *label,
								char **labels_arr);
int								lstlen(t_main *main);
void							reverse_main_list(t_main **list);
void							check_uniqueness_of_labels(t_main *main);
char							*change_base(char *from, int base_from,
											int base_to, int fl);
void							replace_labels_with_numbers(t_main **main);
void							translate_to_byte_code(t_header *header,
								t_main *main, char *filename);
void							write_exec_code(int fd_output, t_main *main);
void							write_comment(int fd_output, t_header *header);
int								ft_atoi_registers(const char *str);
void							write_registry(int fd_output, t_main *main,
								int num_arg);
void							write_direct(int fd_output, t_main *main,
								int num_arg);
void							write_indirect(int fd_output, t_main *main,
								int num_arg);
void							replace_label(unsigned int byte_bias,
								t_main **main, int arg_num);
void							find_label(t_main *iter_main,
								int *declared_label, char *label);
t_main							*new_op_setup(t_main **main);
int								check_after_label(char **line,
								t_indexes *indexes);
t_indexes						*indexes_init(int label_or_op_start);
void							skip_spaces(char *line, int *index);
void							check_for_null(char *line, int *index);
void							dump_champion(t_header *header, t_main *main);
void							disassemble(char *filename);
unsigned int					find_program_size(t_main *main);
void							translate_to_main(t_main *main, int fd_input);
unsigned int					translate_to_header(t_header **header,
								int fd_input);
void							error_exit6(int value, int num_line,
								int symbol);
void							check_slash_zero(int fd_input, int index);
int								check_slash_zero_and_exit(int fd_input, int index, t_main *main);

#endif
