/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_12.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 01:08:06 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/29 22:42:34 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		write_comment(int fd_output, t_header *header)
{
	unsigned char	bytes[COMMENT_LENGTH];
	int				i;

	i = 0;
	while (header->comment[i])
	{
		bytes[i] = (header->comment[i]) & 0xFF;
		i++;
	}
	while (i < COMMENT_LENGTH)
	{
		bytes[i] = 0x00;
		i++;
	}
	write(fd_output, bytes, COMMENT_LENGTH);
}

void		write_num_of_op(int fd_output, t_main *main)
{
	unsigned char	byte[1];

	byte[0] = (main->num_of_op + 1) & 0xFF;
	write(fd_output, byte, 1);
}

void		write_binary_code_of_command(char **tmp,
							int num_arg, t_main *main)
{
	if (main->args[num_arg][0] == 'r')
	{
		(*tmp)[num_arg * 2] = '0';
		(*tmp)[num_arg * 2 + 1] = '1';
	}
	else if (main->args[num_arg][0] == '%')
	{
		(*tmp)[num_arg * 2] = '1';
		(*tmp)[num_arg * 2 + 1] = '0';
	}
	else
	{
		(*tmp)[num_arg * 2] = '1';
		(*tmp)[num_arg * 2 + 1] = '1';
	}
}

void		write_arg_types_code(int fd_output, t_main *main, char *tmp)
{
	int				num_arg;
	char			*num;
	unsigned char	byte[1];

	num_arg = -1;
	while (++num_arg < g_op_tab[main->num_of_op].num_of_args)
		write_binary_code_of_command(&tmp, num_arg, main);
	while (num_arg < 4)
	{
		tmp[num_arg * 2] = '0';
		tmp[num_arg * 2 + 1] = '0';
		num_arg++;
	}
	if (!(num = change_base(tmp, 2, 10, 0)))
		error_exit(e_malloc_error, 0, 0);
	byte[0] = ft_atoi_long(num) & 0xFF;
	write(fd_output, byte, 1);
	free(num);
}

void		write_exec_code(int fd_output, t_main *main)
{
	char			*tmp;
	int				num_arg;

	if (!(tmp = (char *)malloc(sizeof(char) * 9)))
		error_exit(e_malloc_error, 0, 0);
	tmp[8] = '\0';
	while (main)
	{
		write_num_of_op(fd_output, main);
		if (g_op_tab[main->num_of_op].arg_type_code)
			write_arg_types_code(fd_output, main, tmp);
		num_arg = -1;
		while (++num_arg < g_op_tab[main->num_of_op].num_of_args)
			if (main->args[num_arg][0] == 'r')
				write_registry(fd_output, main, num_arg);
			else if (main->args[num_arg][0] == '%')
				write_direct(fd_output, main, num_arg);
			else
				write_indirect(fd_output, main, num_arg);
		main = main->next;
	}
	free(tmp);
}
