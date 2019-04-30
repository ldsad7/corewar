/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:47:05 by mwunsch           #+#    #+#             */
/*   Updated: 2019/04/28 02:46:51 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void			kill_process(t_process *prev, t_process *cur,
							t_vm *vm, int first)
{
	if (first)
		vm->process = cur->next;
	else
		prev->next = cur->next;
	// int i = -1;
	// while (++i < vm->len_arr)
	// 	if (vm->arr[i] == cur)
	// 	{
	// 		vm->arr[i] = NULL;
	// 		break ;
	// 	}
	free(cur);
	cur = NULL;
	vm->num_process--;
	vm->count_enter_kill++;
}

t_process		*add_process(int location, int master, t_process *prev,
							t_vm *vm)
{
	t_process	*p;

	p = new_process(location, master, vm);
	p->next = prev;
	return (p);
}

t_process		*new_process(int location, int master, t_vm *vm)
{
	t_process	*p;
	int			i;

	if (!(p = (t_process *)malloc(sizeof(t_process))))
		error_exit(e_malloc_error, 0, 0);
	p->location = location;
	p->location_prev = 0;
	p->master = master;
	p->next = NULL;
	p->command = 0;
	p->cycles_before_live = 0;
	p->cycles_before_execution = 0;
	p->reg[0] = (master + 1) * -1;
	p->num_in_list = vm->all_processes + 1;
	i = 0;
	while (++i < REG_NUMBER)
		p->reg[i] = 0;
	vm->all_processes++;
	vm->num_process++;
	return (p);
}

void			bots_to_map(t_vm *vm)
{
	int				i;
	int				step;
	t_process		*p;

	p = new_process(0, 0, vm);
	step = MEM_SIZE / vm->num_bots;
	i = -1;
	while (++i < vm->num_bots)
	{
		ft_memcpy(vm->map + i * step, vm->bot[i].weapon,
				vm->bot[i].weapon_size);
		if (i)
			p = add_process(i * step, i, p, vm);
	}
	vm->process = p;
}
