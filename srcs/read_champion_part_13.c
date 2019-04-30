/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_13.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:45:08 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/30 01:11:35 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		write_registry(int fd_output, t_main *main, int num_arg)
{
	char			*num;
	unsigned char	byte[1];

	if (!(num = ft_strsub(main->args[num_arg], 1,
	ft_strlen(main->args[num_arg]) - 1)))
		error_exit(e_malloc_error, 0, 0);
	byte[0] = ft_atoi_long(num) & 0xFF;
	write(fd_output, byte, 1);
	free(num);
}

void		write_direct(int fd_output, t_main *main, int num_arg)
{
	char			*num;
	int				number;
	unsigned char	bytes[4];

	if (!(num = ft_strsub(main->args[num_arg], 1,
	ft_strlen(main->args[num_arg]) - 1)))
		error_exit(e_malloc_error, 0, 0);
	if (g_op_tab[main->num_of_op].size_of_t_dir == 4)
	{
		number = ft_atoi(num);
		bytes[0] = (number >> 24) & 0xFF;
		bytes[1] = (number >> 16) & 0xFF;
		bytes[2] = (number >> 8) & 0xFF;
		bytes[3] = number & 0xFF;
		write(fd_output, bytes, 4);
	}
	else
	{
		number = ft_atoi(num);
		bytes[0] = (number >> 8) & 0xFF;
		bytes[1] = number & 0xFF;
		write(fd_output, bytes, 2);
	}
	free(num);
}

void		write_indirect(int fd_output, t_main *main, int num_arg)
{
	unsigned char	bytes[2];
	int				number;

	number = ft_atoi(main->args[num_arg]);
	bytes[0] = (number >> 8) & 0xFF;
	bytes[1] = number & 0xFF;
	write(fd_output, bytes, 2);
}

void		replace_label(unsigned int byte_bias, t_main **main, int arg_num)
{
	char	*num;
	char	*tmp;

	if (!(num = ft_itoa(byte_bias)))
		error_exit(e_malloc_error, (*main)->args_row_num, (*main)->args_symbols_nums[arg_num] + 1);
	if (ft_strlen((*main)->args[arg_num]) > 1
		&& (*main)->args[arg_num][0] == DIRECT_CHAR
		&& (*main)->args[arg_num][1] == LABEL_CHAR)
	{
		if (!(tmp = ft_strsub((*main)->args[arg_num], 0, 1)))
			error_exit(e_malloc_error, (*main)->args_row_num, (*main)->args_symbols_nums[arg_num] + 1);
		// free((*main)->args[arg_num]);
		(*main)->old_args[arg_num] = (*main)->args[arg_num];
		if (!((*main)->args[arg_num] = ft_strjoin(tmp, num)))
			error_exit(e_malloc_error, (*main)->args_row_num, (*main)->args_symbols_nums[arg_num] + 1);
		free(tmp);
		free(num);
	}
	else if ((*main)->args[arg_num][0] == LABEL_CHAR)
	{
		// free((*main)->args[arg_num]);
		(*main)->old_args[arg_num] = (*main)->args[arg_num];
		(*main)->args[arg_num] = num;
	}
}

void		find_label(t_main *iter_main, int *declared_label, char *label)
{
	t_list	*labels;

	labels = iter_main->labels;
	while (!*declared_label && labels)
	{
		if (!ft_strcmp(labels->content, label))
		{
			*declared_label = 1;
			break ;
		}
		labels = labels->next;
	}
}
