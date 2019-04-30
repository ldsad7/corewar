/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:41:34 by mwunsch           #+#    #+#             */
/*   Updated: 2019/04/30 01:54:11 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

t_params		*g_params;

void			test_print(t_vm *vm)
{
	int i = -1;

	ft_printf("________________ARENA__________________\n");
	ft_print_memory(vm->map, MEM_SIZE, vm, 0);
	ft_printf("\n\n");
	ft_printf("num_bots %d\n", vm->num_bots);
	while (++i < vm->num_bots)
	{
		ft_printf("vm->bot[%d].name %s\n", i, vm->bot[i].name);
		ft_printf("vm->bot[%d].weapon_size %d\n", i, vm->bot[i].weapon_size);
	}
	ft_printf("nbr_cycles %d\n", vm->nbr_cycles);
	ft_printf("nbr_all_cycles %d\n", vm->nbr_all_cycles);
	ft_printf("live_counter %d\n", vm->live_counter);
	ft_printf("cycle_to_die %d\n", vm->cycle_to_die);
	ft_printf("last_alive_bot %d\n", vm->last_alive_bot);
	ft_printf("nbr_live_checks %d\n", vm->nbr_live_checks);
	ft_printf("flag_a %d\n", vm->flag_a);
	ft_printf("flag_d %d\n", vm->flag_d);
	ft_printf("flag_v %d\n", vm->flag_v);
	ft_printf("flag_info %d\n", vm->flag_info);
	ft_printf("num_process %d\n", vm->num_process);
	ft_printf("all_processes %d\n", vm->all_processes);
	ft_printf("process->location %d\n", vm->process->location);
	ft_printf("process->carry %d\n", vm->process->carry);
	ft_printf("process->master(index) %d\n", vm->process->master);
	ft_printf("process->reg: \n");
	while (i < REG_NUMBER)
	{
		ft_printf("reg[%d] = %d\n", i, vm->process->reg[i]);
		i++;
	}
	ft_printf("process->command %d\n", vm->process->command);
}

void			introduction_of_contestants(t_vm *vm)
{
	int			i;

	ft_printf("Introducing contestants...\n");
	i = -1;
	while (++i < vm->num_bots)
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
		i + 1, vm->bot[i].weapon_size, vm->bot[i].name, vm->bot[i].comment);
}

void			vm_init(t_vm *vm)
{
	int			i;

	vm->process = NULL;
	vm->num_process = 0;
	vm->all_processes = 0;
	vm->nbr_cycles = -1;
	vm->live_counter = 0;
	vm->nbr_live_checks = 0;
	vm->nbr_all_cycles = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->flag_a = 0;
	vm->flag_d = -1;
	vm->flag_v = 0;
	vm->flag_info = 0;
	vm->last_alive_bot = -1;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		vm->bot[i].name = NULL;
		vm->bot[i].comment = NULL;
		vm->bot[i].weapon = NULL;
		vm->bot[i].weapon_size = 0;
	}
	if (!(vm->map = ft_memalloc(MEM_SIZE)))
		error_exit(e_malloc_error, 0, 0);
	// vm->len_arr = -1; // to be deleted
	vm->count_enter_kill = 0;
}

void			free_vm(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < vm->num_bots)
	{
		free(vm->bot[i].comment);
		free(vm->bot[i].name);
		free(vm->bot[i].weapon);
	}
	free(vm->map);
}

// 	t_visual			visual;

int				main(int argc, char **argv)
{
	t_vm	vm;

	if (argc < 2)
		error_exit(e_no_arguments_for_corewar, 0, 0);
	vm_init(&vm);
	flags_checker(argc, argv, &vm);
	add_bots(argc, argv, &vm);
	bots_to_map(&vm);
	// test_print(&vm);
	introduction_of_contestants(&vm);
	if (vm.flag_v)
	{
		print_curses(vm.map, &vm);
		init_visual_statistics(&vm);
		init_chat(&vm);
		random_chat(&vm);
	}
	lets_fight(&vm);
	free_vm(&vm);
	// ft_printf("%d\n", vm.nbr_all_cycles);
	// test_print(&vm);
	return (0);
}
