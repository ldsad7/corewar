/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_6.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 01:19:38 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/29 23:10:39 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

int			ft_atoi_registers_and_index(const char *str, int *index)
{
	int		res;

	res = 0;
	while (str[*index + 1] >= '0' && str[*index + 1] <= '9')
	{
		res = res * 10 + (str[*index + 1] - '0');
		(*index)++;
	}
	return (res);
}

void		read_registry(t_main **new, int *num_args, int *index, char *line)
{
	char	*tmp;
	int		r_nr;

	r_nr = ft_atoi_registers_and_index(line, index);
	if (g_op_tab[(*new)->num_of_op].args[*num_args] & T_REG)
	{
		tmp = ft_itoa(r_nr);
		if (!((*new)->args[(*num_args)++] = ft_strjoin("r", tmp)))
			error_exit(e_malloc_error, g_params->num_line, *index + 1);
		*index += 1;
		free(tmp);
	}
	else
		error_exit(e_incorrect_argument, g_params->num_line, *index + 1);
	(*new)->size_of_op++;
}

void		check_after_argument(char *line, int *index,
								int num_args, t_main **new)
{
	if (num_args < g_op_tab[(*new)->num_of_op].num_of_args
		&& line[*index] != SEPARATOR_CHAR)
		error_exit(e_no_separator, g_params->num_line, *index + 1);
	else if (num_args == g_op_tab[(*new)->num_of_op].num_of_args
		&& line[*index] && line[*index] != COMMENT_CHAR
		&& line[*index] != ALT_COMMENT_CHAR)
		error_exit(e_too_many_arguments, g_params->num_line, *index + 1);
	else
		(*index)++;
}

void		read_reg_dir_indir(t_main **new, char *line, int *index,
								int *num_args)
{
	int		r_nr;

	skip_spaces(line, index);
	if (!(line[*index]) || line[*index] == COMMENT_CHAR
	|| line[*index] == ALT_COMMENT_CHAR)
		error_exit(e_not_enough_arguments, g_params->num_line, *index + 1);
	(*new)->args_symbols_nums[*num_args] = *index;
	if (line[*index] == 'r' && (r_nr = ft_atoi_registers(line + *index + 1))
	&& r_nr < 100)
		read_registry(new, num_args, index, line);
	else if (line[*index] == DIRECT_CHAR)
		read_direct(new, num_args, index, line);
	else
		read_indirect(new, num_args, index, line);
	skip_spaces(line, index);
	check_after_argument(line, index, *num_args, new);
}

void		check_slash_zero(int fd_input, int index)
{
	char	*line_fd;

	if (lseek(fd_input, -1, SEEK_CUR) == -1L)
		error_exit(e_lseek_error, g_params->num_line, index);
	if (!(line_fd = (char *)malloc(sizeof(char) * 1)))
		error_exit(e_malloc_error, g_params->num_line, index);
	read(fd_input, line_fd, 1);
	if (line_fd[0] != '\n')
		error_exit(e_instruction_not_slash_n, g_params->num_line, index);
	free(line_fd);	
}

int			check_slash_zero_and_exit(int fd_input, int index, t_main *main)
{
	int		ret_value;
	char	*line_fd;

	if (lseek(fd_input, -1, SEEK_CUR) == -1L)
		error_exit(e_lseek_error, g_params->num_line, index);
	if (!(line_fd = (char *)malloc(sizeof(char) * 1)))
		error_exit(e_malloc_error, g_params->num_line, index);
	read(fd_input, line_fd, 1);
	ret_value = 0;
	if (line_fd[0] != '\n')
	{
		if (main->num_of_op == -1)
			error_exit(e_no_exec_code, g_params->num_line, 0);
		ret_value = 1;
	}
	free(line_fd);
	return (ret_value);
}

void		read_arguments(char *line, int index, t_main **new, int fd_input)
{
	int		num_args;

	(*new)->size_of_op = 1 + g_op_tab[(*new)->num_of_op].arg_type_code;
	num_args = 0;
	while (num_args < g_op_tab[(*new)->num_of_op].num_of_args)
		read_reg_dir_indir(new, line, &index, &num_args);
	(*new)->args_row_num = g_params->num_line;
	check_slash_zero(fd_input, ft_strlen(line) + 1);
}
