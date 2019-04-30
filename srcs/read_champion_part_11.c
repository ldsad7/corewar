/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_11.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 01:03:22 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/28 01:11:06 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		write_exec_code_size(int fd_output, t_main *main)
{
	long long		size;
	unsigned char	bytes[4];

	size = 0;
	while (main)
	{
		size += main->size_of_op;
		main = main->next;
	}
	if (size > 4294967295)
		error_exit(e_exec_code_size_too_big, 0, 0);
	bytes[0] = (size >> 24) & 0xFF;
	bytes[1] = (size >> 16) & 0xFF;
	bytes[2] = (size >> 8) & 0xFF;
	bytes[3] = size & 0xFF;
	write(fd_output, bytes, 4);
}

void		write_null(int fd_output)
{
	unsigned char	bytes[4];

	bytes[0] = 0x00;
	bytes[1] = 0x00;
	bytes[2] = 0x00;
	bytes[3] = 0x00;
	write(fd_output, bytes, 4);
}

void		write_name(int fd_output, t_header *header)
{
	unsigned char	bytes[PROG_NAME_LENGTH];
	int				i;

	i = 0;
	while (header->prog_name[i])
	{
		bytes[i] = (header->prog_name[i]) & 0xFF;
		i++;
	}
	while (i < PROG_NAME_LENGTH)
	{
		bytes[i] = 0x00;
		i++;
	}
	write(fd_output, bytes, PROG_NAME_LENGTH);
}

void		write_magic_header(int fd_output)
{
	unsigned char	bytes[4];

	bytes[0] = ((unsigned int)COREWAR_EXEC_MAGIC >> 24) & 0xFF;
	bytes[1] = ((unsigned int)COREWAR_EXEC_MAGIC >> 16) & 0xFF;
	bytes[2] = ((unsigned int)COREWAR_EXEC_MAGIC >> 8) & 0xFF;
	bytes[3] = (unsigned int)COREWAR_EXEC_MAGIC & 0xFF;
	write(fd_output, bytes, 4);
}

void		translate_to_byte_code(t_header *header, t_main *main,
									char *filename)
{
	int		fd_output;
	char	*tmp;

	if (!(tmp = ft_strsub(filename, 0, ft_strlen(filename) - 2)))
		error_exit(e_malloc_error, 0, 0);
	if (!(filename = ft_strjoin(tmp, ".cor")))
		error_exit(e_malloc_error, 0, 0);
	free(tmp);
	if ((fd_output = open(filename, O_CREAT|O_TRUNC|O_WRONLY, 0777)) < 0)
		error_exit(e_open_error, 0, 0);
	write_magic_header(fd_output);
	write_name(fd_output, header);
	write_null(fd_output);
	write_exec_code_size(fd_output, main);
	write_comment(fd_output, header);
	write_null(fd_output);
	write_exec_code(fd_output, main);
	close(fd_output);
	ft_printf("Writing output program to %s\n", filename);
	free(filename);
	main = *(&main);
}
