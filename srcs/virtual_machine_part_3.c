/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:15:27 by mwunsch           #+#    #+#             */
/*   Updated: 2019/04/30 01:16:40 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		num_bots_checker(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (!(vm->bot[i].weapon))
			break ;
	vm->num_bots = i;
	while (++i < MAX_PLAYERS)
		if (vm->bot[i].weapon)
			error_exit(e_inconsistent_bot_order, 0, 0);
}

int			skip_flags(char **argv, int i)
{
	if (argv[i][1] == 'a' || argv[i][1] == 'v' || argv[i][1] == 'i')
		return (1);
	else if (argv[i][1] == 'd')
		return (2);
	else if (argv[i][1] == 'n')
		return (3);
	// error_exit(e_incorrect_flag, 0, 0);
	return (0);
}

void		add_bots(int argc, char **argv, t_vm *vm)
{
	int     i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			i += skip_flags(argv, i);
		else
		{
			add_bot(argv[i], -1, vm);
			i++;
		}
	}
	num_bots_checker(vm);
}

int			get_next_bot_index(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (!(vm->bot[i].weapon))
			return (i);
	error_exit(e_too_much_bots, 0, 0);
	return (-1);
}

void		check_and_malloc_variables(char *filename, int *fd,
									t_header **header, t_main **main)
{
	if (!endswith(filename, ".cor"))
		error_exit(e_incorrect_cor_file, 0, 0);
	if ((*fd = open(filename, O_RDONLY)) < 0)
		error_exit(e_open_error, 0, 0);
	if (!(*header = (t_header *)malloc(sizeof(t_header))))
		error_exit(e_malloc_error, 0, 0);
	if (!(*main = (t_main *)malloc(sizeof(t_main))))
		error_exit(e_malloc_error, 0, 0);
}

void		free_main(t_main *main)
{
	int		i;
	t_main	*tmp;

	while (main)
	{
		i = -1;
		while (++i < g_op_tab[main->num_of_op].num_of_args)
		{
			free(main->args[i]);
			// free(main->old_args[i]);
		}
		tmp = main->next;
		free(main);
		main = tmp;
	}
}

void		add_bot(char *filename, int i, t_vm *vm)
{
	int				fd;
	t_header		*header;
	t_main			*main;
	unsigned int	given_size;

	if (i == -1)
		return (add_bot(filename, get_next_bot_index(vm), vm));
	if (vm->bot[i].weapon)
		error_exit(e_bad_argument_in_flag_n, 0, 0);
	check_and_malloc_variables(filename, &fd, &header, &main);
	given_size = translate_to_header(&header, fd);
	vm->bot[i].name = header->prog_name;
	vm->bot[i].comment = header->comment;
	translate_to_main(main, fd);
	vm->bot[i].weapon_size = find_program_size(main);
	if (vm->bot[i].weapon_size != given_size)
		error_exit(e_mismatched_sizes, 0, 0);
	lseek(fd, 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4, 0);
	if (!(vm->bot[i].weapon =
	(unsigned char *)malloc(sizeof(unsigned char) * given_size)))
		error_exit(e_malloc_error, 0, 0);
	read(fd, vm->bot[i].weapon, given_size);
	close(fd);
	free_main(main);
	free(header);
}
