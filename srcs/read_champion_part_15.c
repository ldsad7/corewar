/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_15.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 01:57:33 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/30 00:13:10 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void			check_magic_header(int fd_input)
{
	unsigned char	bytes[4];

	if (read(fd_input, bytes, 4) < 4)
		error_exit(e_cor_file_is_too_short, 1, 0);
	if ((bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3] !=
		(unsigned int)COREWAR_EXEC_MAGIC)
		error_exit(e_incorrect_magic_header, 1, 0);
}

void			read_champion_name(int fd_input, t_header **header)
{
	unsigned char	bytes[PROG_NAME_LENGTH];

	if (read(fd_input, bytes, PROG_NAME_LENGTH) < PROG_NAME_LENGTH)
		error_exit(e_cor_file_is_too_short, 1, 4);
	(*header)->prog_name = ft_strjoin((char *)bytes, "\0");
}

void			read_null_before(int fd_input)
{
	unsigned char	bytes[4];

	if (read(fd_input, bytes, 4) < 4)
		error_exit(e_cor_file_is_too_short, 1, 4 + PROG_NAME_LENGTH);
	if ((bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3] != 0)
		error_exit(e_incorrect_null_sequence, 1, 4 + PROG_NAME_LENGTH);
}

unsigned int	read_champion_exec_code_size(int fd_input)
{
	unsigned int	size;
	unsigned char	bytes[4];

	if (read(fd_input, bytes, 4) < 4)
		error_exit(e_cor_file_is_too_short, 1, 4 + PROG_NAME_LENGTH + 4);
	size = ((bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3]);
	if (size > CHAMP_MAX_SIZE)
		error_exit(e_exec_code_size_is_too_big, 1, 4 + PROG_NAME_LENGTH + 4);
	return (size);
}

void			read_champion_comment(int fd_input, t_header **header)
{
	unsigned char	bytes[COMMENT_LENGTH];

	if (read(fd_input, bytes, COMMENT_LENGTH) < COMMENT_LENGTH)
		error_exit(e_cor_file_is_too_short, 1, 4 + PROG_NAME_LENGTH + 4 + 4);
	(*header)->comment = ft_strjoin((char *)bytes, "\0");
}

void			read_null_after(int fd_input)
{
	unsigned char	bytes[4];

	if (read(fd_input, bytes, 4) < 4)
		error_exit(e_cor_file_is_too_short, 1, 4 + PROG_NAME_LENGTH);
	if ((bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3] != 0)
		error_exit(e_incorrect_null_sequence, 1,
					4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH);
}

unsigned int	translate_to_header(t_header **header, int fd_input)
{
	unsigned int	size;

	check_magic_header(fd_input);
	read_champion_name(fd_input, header);
	read_null_before(fd_input);
	size = read_champion_exec_code_size(fd_input);
	read_champion_comment(fd_input, header);
	read_null_after(fd_input);
	return (size);
}

void			read_num_of_op(t_main **main, unsigned char bytes[4],
								int *read_bytes)
{
	(*main)->num_of_op = bytes[0];
	if ((*main)->num_of_op > NUM_OF_OPS || !(*main)->num_of_op)
		error_exit(e_incorrect_operation_number, 1, *read_bytes);
	(*main)->num_of_op--;
	(*read_bytes)++;
}

/*
** 1 => r
** 2 => direct
** 3 => indirect
*/

void			check_reg(t_main **main, int num_arg,
						int read_bytes, int (*args)[3])
{
	if (!(g_op_tab[(*main)->num_of_op].args[num_arg] & T_REG))
		error_exit(e_incorrect_argument, 1, read_bytes);
	else
		(*args)[num_arg] = 1;
}

void			check_direct(t_main **main, int num_arg,
						int read_bytes, int (*args)[3])
{
	if (!(g_op_tab[(*main)->num_of_op].args[num_arg] & T_DIR))
		error_exit(e_incorrect_argument, 1, read_bytes);
	else
		(*args)[num_arg] = 2;
}

void			check_indirect(t_main **main, int num_arg,
						int read_bytes, int (*args)[3])
{
	if (!(g_op_tab[(*main)->num_of_op].args[num_arg] & T_IND))
		error_exit(e_incorrect_argument, 1, read_bytes);
	else
		(*args)[num_arg] = 3;
}

void			check_nulls(int *num_arg, unsigned char bytes[4],
							int *read_bytes)
{
	while (++(*num_arg) < 4)
		if (((bytes[0] >> (6 - *num_arg * 2)) & 3))
			error_exit(e_incorrect_argument, 1, *read_bytes);
	(*read_bytes)++;
}

void			write_reg(unsigned char bytes[4], int *read_bytes,
						t_main **main, int num_arg)
{
	char *tmp;

	if (!(tmp = ft_itoa_long(bytes[0])))
		error_exit(e_malloc_error, 0, 0);
	if (bytes[0] > REG_NUMBER || !bytes[0])
		error_exit(e_incorrect_argument, 1, *read_bytes);
	(*main)->args[num_arg] = ft_strjoin("r", tmp);
	(*read_bytes)++;
	free(tmp);
}

void			write_dir(unsigned char bytes[4], int *read_bytes,
						t_main **main, int num_arg)
{
	int		num;
	char	*tmp;

	if (g_op_tab[(*main)->num_of_op].size_of_t_dir == 4)
		num = (bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];
	else
		num = (bytes[0] << 8) + bytes[1];
	if (!(tmp = ft_itoa_long(num)))
		error_exit(e_malloc_error, 0, 0);
	(*main)->args[num_arg] = ft_strjoin("%", tmp);
	*read_bytes += g_op_tab[(*main)->num_of_op].size_of_t_dir;
	free(tmp);
}

void			write_indir(unsigned char bytes[4], int *read_bytes,
						t_main **main, int num_arg)
{
	int	num;

	num = (bytes[0] << 8) + bytes[1];
	(*main)->args[num_arg] = ft_itoa_long(num);
	*read_bytes += 2;
}

void			check_main_size_of_op(t_main **main)
{
	if ((*main)->size_of_op)
	{
		if (!((*main)->next = (t_main *)malloc(sizeof(t_main))))
			error_exit(e_malloc_error, 0, 0);
		*main = (*main)->next;
		(*main)->size_of_op = 0;
		(*main)->next = NULL;
	}
}

void			read_arg_type_code(int fd_input, int *read_bytes,
									t_main **main, int (*args)[3])
{
	unsigned char	bytes[4];
	int				num_arg;

	if (g_op_tab[(*main)->num_of_op].arg_type_code)
	{
		if (!read(fd_input, bytes, 1))
			error_exit(e_cor_file_is_too_short, 1, *read_bytes);
		(*read_bytes)++;
		num_arg = -1;
		while (++num_arg < g_op_tab[(*main)->num_of_op].num_of_args)
			if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 1)
				check_reg(main, num_arg, *read_bytes, args);
			else if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 2)
				check_direct(main, num_arg, *read_bytes, args);
			else if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 3)
				check_indirect(main, num_arg, *read_bytes, args);
			else if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 0)
				error_exit(e_incorrect_argument, 1, *read_bytes);
		check_nulls(&num_arg, bytes, read_bytes);
		(*main)->size_of_op++;
	}
	else
		(*args)[0] = 2;
}

int				condition(int *num_arg, t_main **main,
							int args[3])
{
	int				bytes_to_be_read;

	if (++(*num_arg) < g_op_tab[(*main)->num_of_op].num_of_args &&
		(bytes_to_be_read = 1 * (args[*num_arg] == 1)
		+ g_op_tab[(*main)->num_of_op].size_of_t_dir * (args[*num_arg] == 2)
		+ 2 * (args[*num_arg] == 3)))
	{
		(*main)->size_of_op += bytes_to_be_read;
		return (bytes_to_be_read);
	}
	return (0);
}

void			translate_to_main(t_main *main, int fd_input)
{
	unsigned char	bytes[4];
	int				read_bytes;
	int				args[3];
	int				num_arg;
	int				bytes_to_be_read;

	main->size_of_op = 0;
	read_bytes = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	while (read(fd_input, bytes, 1))
	{
		check_main_size_of_op(&main);
		read_num_of_op(&main, bytes, &read_bytes);
		main->size_of_op++;
		read_arg_type_code(fd_input, &read_bytes, &main, &args);
		num_arg = -1;
		while ((bytes_to_be_read = condition(&num_arg, &main, args)))
			if (read(fd_input, bytes, bytes_to_be_read) < bytes_to_be_read)
				error_exit(e_cor_file_is_too_short, 1, read_bytes);
			else if (args[num_arg] == 1)
				write_reg(bytes, &read_bytes, &main, num_arg);
			else if (args[num_arg] == 2)
				write_dir(bytes, &read_bytes, &main, num_arg);
			else if (args[num_arg] == 3)
				write_indir(bytes, &read_bytes, &main, num_arg);
	}
}

void			print_header_and_main(t_header *header, t_main *main)
{
	int		num_arg;

	ft_printf("%s \"%s\"\n", NAME_CMD_STRING, header->prog_name);
	ft_printf("%s \"%s\"\n", COMMENT_CMD_STRING, header->comment);
	if (main->num_of_op + 1)
		write(1, "\n", 1);
	while (main)
	{
		ft_printf("%s", g_op_tab[main->num_of_op].name);
		num_arg = -1;
		while (++num_arg < g_op_tab[main->num_of_op].num_of_args)
		{
			ft_printf(" %s", main->args[num_arg]);
			if (num_arg + 1 < g_op_tab[main->num_of_op].num_of_args)
				write(1, ",", 1);
		}
		write(1, "\n", 1);
		main = main->next;
	}
}

void			disassemble(char *filename)
{
	int				fd_input;
	t_header		*header;
	t_main			*main;
	unsigned int	given_size;
	unsigned int	actual_size;

	if (!endswith(filename, ".cor"))
		error_exit(e_incorrect_cor_file, 0, 0);
	if ((fd_input = open(filename, O_RDONLY)) < 0)
		error_exit(e_open_error, 0, 0);
	if (!(header = (t_header *)malloc(sizeof(t_header))))
		error_exit(e_malloc_error, 0, 0);
	if (!(main = (t_main *)malloc(sizeof(t_main))))
		error_exit(e_malloc_error, 0, 0);
	given_size = translate_to_header(&header, fd_input);
	translate_to_main(main, fd_input);
	actual_size = find_program_size(main);
	if (actual_size != given_size)
		error_exit(e_mismatched_sizes, 0, 0);
	print_header_and_main(header, main);
	close(fd_input);
	exit(0);
}
