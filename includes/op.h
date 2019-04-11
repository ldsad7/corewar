/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2019/04/12 02:18:15 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define ALT_COMMENT_CHAR		';'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char					t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct					s_header
{
	unsigned int				magic;
	char						*prog_name;
	unsigned int				prog_size;
	char						*comment;
	int							num_line;
}								t_header;

typedef struct					s_main
{
	int							num_of_op;
	int							size_of_op;
	char						*args[3];
	char						*label;
	struct s_main				*next;
	int							num_line;
}								t_main;

# include "libft.h"

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

# define NUM_OF_OPS				16

extern t_op g_op_tab[NUM_OF_OPS];

enum {
	e_num_args_not_one,
	e_incorrect_s_file,
	e_open_error,
	e_malloc_error,
	e_invalid_instruction,
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
	e_not_enoguh_arguments,
	e_incorrect_symbol_in_label,
	// e_empty_file,
	// e_error_reading_file,
	// e_last_instruction_not_slash_n
};

void							error_exit(int value, int num_line, int symbol);

#endif
