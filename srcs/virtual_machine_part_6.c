/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_6.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:11:35 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/30 04:39:51 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

int		modulo_mem_size(int value)
{
	if (value >= 0)
		return (value % MEM_SIZE);
	else
		return (MEM_SIZE + (value % MEM_SIZE));
}

void	print_adv(int right, int left, t_vm *vm)
{
	if (right > left)
		ft_printf("ADV %d (0x%04x -> 0x%04x) ", right - left, left, right);
	else
		ft_printf("ADV %d (0x%04x -> 0x%04x) ", MEM_SIZE - left + right, left, left + (MEM_SIZE - left + right));
	while (left != right)
	{
		print_hex(vm->map[left]);
		write(1, " ", 1);
		left = modulo_mem_size(left + 1);
	}
	write(1, "\n", 1);
}

void	apply_operation(t_process *process, t_vm *vm)
{
	process->location = modulo_mem_size(process->location);
	if (0x01 <= process->command && process->command <= 0x10)
		process_operation(process->command - 1, process, vm);
	else
		process->location++;
	process->location = modulo_mem_size(process->location);
}

void	ft_memcpy_overflow(const void *dst, const void *src, int n, int start)
{
	int	cntr;
	int i;

	if (!dst || !src)
		return ;
	i = start;
	cntr = 0;
	while (cntr < n)
	{
		((unsigned char *)dst)[cntr] = ((unsigned char *)src)[modulo_mem_size(i)];
		cntr++;
		i++;
	}
}


void	ft_cpymem_overflow(t_vm *vm, const void *src, int n, int start)
{
	int	cntr;
	int i;
	const void *dst;

	dst = vm->map;
	if (!dst || !src)
		return ;
	i = 0;
	cntr = start;
	while (i < n)
	{
		((unsigned char *)dst)[cntr] = ((unsigned char *)src)[i];
		if (vm->flag_v)
		{
			wmove(vm->visual.win, cntr / 64, cntr % 64 * 3);
			wattron(vm->visual.win, COLOR_PAIR(vm->cur_process->master + 5));
			waddch(vm->visual.win, TAB[vm->map[cntr] / 16]);
			waddch(vm->visual.win, TAB[vm->map[cntr] % 16]);
			wattroff(vm->visual.win, COLOR_PAIR(vm->cur_process->master + 5));
		}
		cntr = modulo_mem_size(cntr + 1);
		i++;
	}
}

/*
** need to add update in visual in all cells except processes cells
*/
// void	ft_cpymem_overflow(const void *dst, const void *src, int n, int start)
// {
// 	int	cntr;
// 	int i;

// 	if (!dst || !src)
// 		return ;
// 	i = 0;
// 	cntr = start;
// 	while (i < n)
// 	{
// 		((unsigned char *)dst)[cntr] = ((unsigned char *)src)[i];
// 		cntr = modulo_mem_size(cntr + 1);
// 		i++;
// 	}
// }

/*
** 1 => r
** 2 => direct
** 3 => indirect
*/

int		check_registry(int num_of_op, int num_arg,
						int (*args)[4])
{
	(*args)[num_arg] = 1;
	if (g_op_tab[num_of_op].args[num_arg] & T_REG)
		return (0);
	else
		return ((*args)[num_arg]);
}

int		check_dir(int num_of_op, int num_arg,
					int (*args)[4])
{
	(*args)[num_arg] = 2;
	if (g_op_tab[num_of_op].args[num_arg] & T_DIR)
		return (0);
	else
		return ((*args)[num_arg]);
}

int		check_indir(int num_of_op, int num_arg,
					int (*args)[4])
{
	(*args)[num_arg] = 3;
	if (g_op_tab[num_of_op].args[num_arg] & T_IND)
		return (0);
	else
		return ((*args)[num_arg]);
}

int		find_size_of_args(int args[4], int num_of_op, int num_arg)
{
	int		i;
	int		sum;

	sum = 0;
	i = 0;
	while (i < num_arg)
	{
		if (args[i] == 1)
			sum += 1;
		else if (args[i] == 2)
			sum += g_op_tab[num_of_op].size_of_t_dir;
		else if (args[i] == 3)
			sum += IND_SIZE;
		i++;
	}
	return (sum);
}

void	process_operation(int num_of_op, t_process *process, t_vm *vm)
{
	int				args[4];
	unsigned char	bytes[4];
	int				num_arg;
	int				incorrect_args; // were there incorrect arguments?

	process->location_arg = process->location;
	process->location_arg = modulo_mem_size(process->location_arg + 1); // skip operation byte
	incorrect_args = 0;
	if (g_op_tab[num_of_op].arg_type_code)
	{
		ft_memcpy_overflow(bytes, vm->map, 1, process->location_arg);
		process->location_arg = modulo_mem_size(process->location_arg + 1); // skip arg types code byte
		num_arg = -1;
		while (++num_arg < g_op_tab[num_of_op].num_of_args)
		{
			if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 1)
			{
				if (!(incorrect_args += check_registry(num_of_op, num_arg, &args)))
				{
					ft_memcpy_overflow(bytes + 1, vm->map, 1,
					process->location_arg + find_size_of_args(args, num_of_op, num_arg));
					if (bytes[1] == 0 || bytes[1] > REG_NUMBER)
						incorrect_args++;
				}
			}
			else
				incorrect_args += else_branch(bytes, num_arg, &args, num_of_op);
		}
		if (incorrect_args) // NB: если, скажем, последний аргумент ненулевой, мы на его размер НЕ сдвигаемся
		{
			process->location_arg = modulo_mem_size(process->location_arg + find_size_of_args(args, num_of_op, g_op_tab[num_of_op].num_of_args)); // skip arguments
			if (vm->flag_info)
				print_adv(process->location_arg, process->location, vm);
		}
	}
	if (!incorrect_args)
		read_correct_arguments(num_of_op, process, vm, args);
	process->location = process->location_arg;
}

int		else_branch(unsigned char bytes[4], int num_arg,
					int (*args)[4], int num_of_op)
{
	int		incorrect_args;

	incorrect_args = 0;
	if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 2)
		incorrect_args += check_dir(num_of_op, num_arg, args);
	else if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 3)
		incorrect_args += check_indir(num_of_op, num_arg, args);
	else if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 0)
	{
		(*args)[num_arg] = 0;
		incorrect_args++;
	}
	return (incorrect_args);
}

void	read_correct_arguments(int num_of_op, t_process *process,
								t_vm *vm, int args[4])
{
	if (!num_of_op)
		process->cycles_before_live++;
	if (num_of_op == 0)
		live_operation(num_of_op, process, vm); // ok
	else if (num_of_op == 1 || num_of_op == 12)
		ld_operation(num_of_op, process, vm, args); // ok
	else if (num_of_op == 2)
		st_operation(process, vm, args); // ok
	else if (num_of_op == 3 || num_of_op == 4)
		add_sub_operations(num_of_op, process, vm); // ok
	else if (num_of_op == 5 || num_of_op == 6 || num_of_op == 7)
		and_or_xor_operations(num_of_op, process, vm, args); // ok
	else if (num_of_op == 8)
		zjmp_operation(num_of_op, process, vm); // ok
	else if (num_of_op == 9 || num_of_op == 13)
		ldi_operation(num_of_op, process, vm, args); // ok
	else if (num_of_op == 10)
		sti_operation(num_of_op, process, vm, args); // ok
	else if (num_of_op == 11 || num_of_op == 14)
		fork_operation(num_of_op, process, vm); // ok
	else if (num_of_op == 15)
		aff_operation(process, vm); // ok
}

int				read_dir_value(int num_of_op, unsigned char bytes[4])
{
	int			value;

	if (g_op_tab[num_of_op].size_of_t_dir == 4)
		value = (bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];
	else
		value = (short int)((bytes[0] << 8) + bytes[1]);
	return (value);
}

int				read_direct_argument(int num_of_op, t_process *process, t_vm *vm)
{
	int				dir_arg;
	unsigned char	bytes[DIR_SIZE];

	ft_memcpy_overflow(bytes, vm->map, g_op_tab[num_of_op].size_of_t_dir, process->location_arg);
	dir_arg = read_dir_value(num_of_op, bytes);
	process->location_arg = modulo_mem_size(process->location_arg + g_op_tab[num_of_op].size_of_t_dir);
	return (dir_arg);
}

int				read_indirect_argument(t_process *process, t_vm *vm)
{
	int				indir_arg;
	unsigned char	bytes[DIR_SIZE];
	short int		bias;

	ft_memcpy_overflow(bytes, vm->map, IND_SIZE, process->location_arg);
	bias = (bytes[0] << 8) + bytes[1];
	ft_memcpy_overflow(bytes, vm->map, 4, process->location + (bias % IDX_MOD));
	indir_arg = (bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];
	process->location_arg = modulo_mem_size(process->location_arg + IND_SIZE);
	return (indir_arg);
}

int				read_registry_argument(t_process *process, t_vm *vm, int *read_value)
{
	unsigned char	bytes[1];

	ft_memcpy_overflow(bytes, vm->map, 1, modulo_mem_size(process->location_arg));
	process->location_arg = modulo_mem_size(process->location_arg + 1); // skip a registry
	*read_value = process->reg[bytes[0] - 1];
	return (bytes[0]);
}

int				write_registry_argument(t_process *process, t_vm *vm, int value)
{
	unsigned char	bytes[1];

	ft_memcpy_overflow(bytes, vm->map, 1, process->location_arg);
	process->location_arg = modulo_mem_size(process->location_arg + 1); // skip a registry
	process->reg[bytes[0] - 1] = value;
	return (bytes[0]);
}

void	live_operation(int num_of_op, t_process *process, t_vm *vm)
{
	int				num;
	unsigned char	bytes[4];

	vm->live_counter++;
	// process->live = 1; // засчитываем, что каретка, которая выполняет операцию live, жива
	process->cycles_before_live = 0; // vm->nbr_cycles // обновляем количество циклов, после последнего выполнения операции live
	ft_memcpy_overflow(bytes, vm->map, g_op_tab[num_of_op].size_of_t_dir, process->location_arg);
	if (g_op_tab[num_of_op].size_of_t_dir == 4)
	{
		num = (bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];
		if (vm->flag_info)
			ft_printf("P %4d | live %d\n", process->num_in_list, num);
		if (num < 0 && -num <= vm->num_bots)
		{
			vm->last_alive_bot = -num - 1; // засчитываем, что данный игрок жив
			if (vm->flag_info)
				ft_printf("Player %d (%s) is said to be alive\n", -num, vm->bot[-num - 1].name);
		}
	}
	else
	{
		num = (short int)((bytes[0] << 8) + bytes[1]);
		if (vm->flag_info)
			ft_printf("P %4d | live %d\n", process->num_in_list, num);
		if (num < 0 && -num <= vm->num_bots)
		{
			vm->last_alive_bot = -num - 1; // засчитываем, что данный игрок жив
			if (vm->flag_info)
				ft_printf("Player %d (%s) is said to be alive\n", -num, vm->bot[-num - 1].name);
		}
	}
	process->location_arg = modulo_mem_size(process->location_arg + g_op_tab[num_of_op].size_of_t_dir);
	if (vm->flag_info)
		print_adv(process->location_arg, process->location, vm);
}

void			ld_operation(int num_of_op, t_process *process, t_vm *vm, int args[4])
{
	int				dir_or_indir;
	int				num_of_reg;
	unsigned char	bytes[4];

	dir_or_indir = 0;
	if (args[0] == 2)
		dir_or_indir = read_direct_argument(num_of_op, process, vm);
	else if (args[0] == 3)
	{
		ft_memcpy_overflow(bytes, vm->map, IND_SIZE, process->location_arg);
		if (num_of_op == 1)
			dir_or_indir = ((short int)((bytes[0] << 8) + bytes[1]) % IDX_MOD);
		else // num_of_op == 12
			dir_or_indir = (short int)((bytes[0] << 8) + bytes[1]);
		ft_memcpy_overflow(bytes, vm->map, g_op_tab[num_of_op].size_of_t_dir,
		process->location + dir_or_indir);
		process->location_arg = modulo_mem_size(process->location_arg + IND_SIZE);
		dir_or_indir = read_dir_value(num_of_op, bytes);
	}
	num_of_reg = write_registry_argument(process, vm, dir_or_indir);
	process->carry = (!dir_or_indir);
	if (vm->flag_info)
	{
		ft_printf("P %4d | %s %d r%d\n", process->num_in_list,
		num_of_op == 1 ? "ld" : "lld", dir_or_indir, num_of_reg);
		print_adv(process->location_arg, process->location, vm);
	}
}

void	st_operation(t_process *process, t_vm *vm, int args[4])
{
	unsigned char	bytes[4];
	int				value_from_reg;
	int				first_num_of_reg;
	int				second_num_of_reg;
	short int		address;

	first_num_of_reg = read_registry_argument(process, vm, &value_from_reg);
	if (args[1] == 1)
		second_num_of_reg = write_registry_argument(process, vm, value_from_reg);
	else if (args[1] == 3)
	{
		ft_memcpy_overflow(bytes, vm->map, IND_SIZE, process->location_arg);
		address = ((short int)((bytes[0] << 8) + bytes[1])) % IDX_MOD;
		bytes[0] = (value_from_reg >> 24) & 0xFF;
		bytes[1] = (value_from_reg >> 16) & 0xFF;
		bytes[2] = (value_from_reg >> 8) & 0xFF;
		bytes[3] = value_from_reg & 0xFF;
		// ft_cpymem_overflow(vm->map, bytes, 4, process->location + address);
		ft_cpymem_overflow(vm, bytes, 4, process->location + address);
		process->location_arg = modulo_mem_size(process->location_arg + IND_SIZE); // skip IND
	}
	if (vm->flag_info)
	{
		if (args[1] == 1)
			ft_printf("P %4d | st r%d r%d\n", process->num_in_list, first_num_of_reg, second_num_of_reg);
		else // args[1] == 3
			ft_printf("P %4d | st r%d %d\n", process->num_in_list, first_num_of_reg, address); // % IDX_MOD или без?
		print_adv(process->location_arg, process->location, vm);
	}
}

void	add_sub_operations(int num_of_op, t_process *process, t_vm *vm)
{
	int				first_value;
	int				second_value;
	int				value_to_be_written;
	int				num_of_first_reg;
	int				num_of_second_reg;
	int				num_of_third_reg;

	num_of_first_reg = read_registry_argument(process, vm, &first_value);
	num_of_second_reg = read_registry_argument(process, vm, &second_value);
	if (num_of_op == 3)
		value_to_be_written = first_value + second_value;
	else // num_of_op == 4
		value_to_be_written = first_value - second_value;
	num_of_third_reg = write_registry_argument(process, vm, value_to_be_written);
	process->carry = (!value_to_be_written);
	if (vm->flag_info)
	{
		ft_printf("P %4d | %s r%d r%d r%d\n", process->num_in_list,
		num_of_op == 3 ? "add" : "sub", num_of_first_reg, num_of_second_reg, num_of_third_reg);
		print_adv(process->location_arg, process->location, vm);
	}
}

void			and_or_xor_operations(int num_of_op, t_process *process, t_vm *vm, int args[4])
{
	int			first_value;
	int			second_value;
	int			value_to_be_written;
	int			num_of_reg;

	if (args[0] == 1)
		read_registry_argument(process, vm, &first_value);
	else if (args[0] == 2)
		first_value = read_direct_argument(num_of_op, process, vm);
	else if (args[0] == 3)
		first_value = read_indirect_argument(process, vm);
	if (args[1] == 1)
		read_registry_argument(process, vm, &second_value);
	else if (args[1] == 2)
		second_value = read_direct_argument(num_of_op, process, vm);
	else if (args[1] == 3)
		second_value = read_indirect_argument(process, vm);
	if (num_of_op == 5)
		value_to_be_written = first_value & second_value;
	else if (num_of_op == 6)
		value_to_be_written = first_value | second_value;
	else // num_of_op == 7
		value_to_be_written = first_value ^ second_value;
	num_of_reg = write_registry_argument(process, vm, value_to_be_written);
	process->carry = (!value_to_be_written);
	if (vm->flag_info)
	{
		if (num_of_op == 5)
			ft_printf("P %4d | and %d %d r%d\n", process->num_in_list, first_value, second_value, num_of_reg);
		else if (num_of_op == 6)
			ft_printf("P %4d | or %d %d r%d\n", process->num_in_list, first_value, second_value, num_of_reg);
		else // num_of_op == 7
			ft_printf("P %4d | xor %d %d r%d\n", process->num_in_list, first_value, second_value, num_of_reg);
		print_adv(process->location_arg, process->location, vm);
	}
}

void			zjmp_operation(int num_of_op, t_process *process, t_vm *vm)
{
	int		dir_argument;

	dir_argument = read_direct_argument(num_of_op, process, vm);
	if (process->carry)
	{
		process->location_arg = process->location + dir_argument % IDX_MOD;
		if (vm->flag_info)
			ft_printf("P %4d | zjmp %d OK\n", process->num_in_list, dir_argument);
	}
	else
	{
		if (vm->flag_info)
		{
			ft_printf("P %4d | zjmp %d FAILED\n", process->num_in_list, dir_argument);
			print_adv(process->location_arg, process->location, vm);
		}
	}
}

void			ldi_operation(int num_of_op, t_process *process, t_vm *vm, int args[4])
{
	unsigned char	bytes[4];
	int				first_value;
	int				second_value;
	int				value_to_be_written;
	int				bias;
	int				num_of_reg;

	if (args[0] == 1)
		read_registry_argument(process, vm, &first_value);
	else if (args[0] == 2)
		first_value = read_direct_argument(num_of_op, process, vm);
	else // (args[0] == 3)
		first_value = read_indirect_argument(process, vm);
	if (args[1] == 1)
		read_registry_argument(process, vm, &second_value);
	else // (args[1] == 2)
		second_value = read_direct_argument(num_of_op, process, vm);
	if (num_of_op == 9)
		bias = (first_value + second_value) % IDX_MOD;
	else // num_of_op == 13
		bias = first_value + second_value;
	ft_memcpy_overflow(bytes, vm->map, 4, process->location + bias);
	value_to_be_written = (bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];
	num_of_reg = write_registry_argument(process, vm, value_to_be_written);
	if (num_of_op == 13)
		process->carry = (!value_to_be_written);
	if (vm->flag_info)
	{
		ft_printf("P %4d | %s %d %d r%d\n", process->num_in_list,
		num_of_op == 9 ? "ldi" : "lldi", first_value, second_value, num_of_reg);
		if (num_of_op == 9)
			ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
			first_value, second_value, first_value + second_value,
			modulo_mem_size(process->location + bias));
		else
			ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
			first_value, second_value, first_value + second_value,
			modulo_mem_size(process->location + bias));
		print_adv(process->location_arg, process->location, vm);
	}
}

void	sti_operation(int num_of_op, t_process *process, t_vm *vm, int args[4])
{
	unsigned char	bytes[4];
	int				value_to_be_written;
	int				second_value;
	int				third_value;
	int				num_of_reg;

	second_value = 0;
	third_value = 0;
	num_of_reg = read_registry_argument(process, vm, &value_to_be_written);
	if (args[1] == 1)
		read_registry_argument(process, vm, &second_value);
	else if (args[1] == 2)
		second_value = read_direct_argument(num_of_op, process, vm);
	else // (args[1] == 3)
		second_value = read_indirect_argument(process, vm);
	if (args[2] == 1)
		read_registry_argument(process, vm, &third_value);
	else // (args[2] == 2)
		third_value = read_direct_argument(num_of_op, process, vm);
	bytes[0] = (value_to_be_written >> 24) & 0xFF;
	bytes[1] = (value_to_be_written >> 16) & 0xFF;
	bytes[2] = (value_to_be_written >> 8) & 0xFF;
	bytes[3] = value_to_be_written & 0xFF;
	// ft_cpymem_overflow(vm->map, bytes, 4,
	ft_cpymem_overflow(vm, bytes, 4,
	modulo_mem_size(process->location + (second_value + third_value) % IDX_MOD));
	if (vm->flag_info)
	{
		ft_printf("P %4d | sti r%d %d %d\n", process->num_in_list, num_of_reg, second_value, third_value);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
		second_value, third_value, second_value + third_value,
		process->location + (second_value + third_value) % IDX_MOD);
		print_adv(process->location_arg, process->location, vm);
	}
}

void	fork_operation(int num_of_op, t_process *process, t_vm *vm)
{
	int	reg_nr;
	int	dir_arg;

	vm->process = add_process(process->location, process->master, vm->process, vm);
	vm->process->carry = process->carry;
	reg_nr = -1;
	while (++reg_nr < REG_NUMBER)
		vm->process->reg[reg_nr] = process->reg[reg_nr];
	dir_arg = read_direct_argument(num_of_op, process, vm);
	if (num_of_op == 11)
		vm->process->location = process->location + (dir_arg % IDX_MOD);
	else // num_of_op == 14
		vm->process->location = process->location + dir_arg;
	vm->process->location_prev = process->location;
	vm->process->location_arg = process->location_arg;
	vm->process->cycles_before_live = process->cycles_before_live;
	vm->process->cycles_before_execution = process->cycles_before_execution;
	vm->process->command = process->command;
	if (vm->flag_info)
	{
		ft_printf("P %4d | %s %d (%d)\n", process->num_in_list,
		num_of_op == 11 ? "fork" : "lfork", dir_arg, process->location +
		(num_of_op == 11) * (dir_arg % IDX_MOD) + (num_of_op == 14) * dir_arg);
		print_adv(process->location_arg, process->location, vm);
	}
}

void	aff_operation(t_process *process, t_vm *vm)
{
	read_registry_argument(process, vm, &(vm->aff_value));
	vm->aff_value = (unsigned char)vm->aff_value;
	if (vm->flag_a)
		if (!(vm->flag_v))
			ft_printf("Aff: %c\n", vm->aff_value);
	if (vm->flag_info)
		print_adv(process->location_arg, process->location, vm);
}
