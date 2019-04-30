/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwunsch <mwunsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 17:25:31 by mwunsch           #+#    #+#             */
/*   Updated: 2019/04/29 16:18:58 by mwunsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		get_flag_n(char *num, char *filename, t_vm *vm)
{
	int		i;
	int		number;

	i = 0;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			error_exit(e_bad_argument_in_flag_n, 0, 0);
		i++;
	}
	if ((number = ft_atoi(num)) > MAX_PLAYERS || number <= 0)
		error_exit(e_bad_argument_in_flag_n, 0, 0);
	add_bot(filename, number - 1, vm);
}

void		get_flag_dump(char *flag, t_vm *vm)
{
	int		i;

	i = 0;
	while (flag[i])
	{
		if (!ft_isdigit(flag[i]))
			error_exit(e_incorrect_argument_after_dump_flag, 0, 0);
		i++;
	}
	vm->nbr_cycles = ft_atoi(flag);
	if (vm->nbr_cycles < 0)  // <= 0 ?
		error_exit(e_incorrect_argument_after_dump_flag, 0, 0);
}

int			get_flags(int argc, char **argv, int i, t_vm *vm)
{
	if (!ft_strcmp(&(argv[i][1]), "dump") ||
		(argv[i][1] == 'd' && argv[i][2] == '\0'))
	{
		if (!(argv[i][2]))
			vm->flag_d = 1;
		if (i + 1 >= argc)
			error_exit(e_not_enough_arguments, 0, 0);
		get_flag_dump(argv[i + 1], vm);
		return (2);
	}
	else if (argv[i][1] == 'n' && argv[i][2] == '\0')
	{
		if (i + 2 >= argc)
			error_exit(e_not_enough_arguments, 0, 0);
		get_flag_n(argv[i + 1], argv[i + 2], vm);
		return (3);
	}
	else if (argv[i][1] == 'a' && argv[i][2] == '\0')
	{
		vm->flag_a = 1;
		return (1);
	}
	else if (!ft_strcmp(&(argv[i][1]), "info"))
	{
		vm->flag_info = 1;
		return (1);
	}
	else if (argv[i][1] == 'v' && argv[i][2] == '\0')
	{
		vm->flag_v = 1;
		return (1);
	}
	error_exit(e_incorrect_flag, 0, 0);
	return (0);
}

void		flags_checker(int argc, char **argv, t_vm *vm)
{
	int		i;

	i = 1;
	while (i < argc)
		if (argv[i][0] == '-')
			i += get_flags(argc, argv, i, vm);
		else
			i++;
}
