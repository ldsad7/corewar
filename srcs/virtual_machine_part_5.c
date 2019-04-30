/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_5.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:19:43 by mwunsch           #+#    #+#             */
/*   Updated: 2019/04/29 21:08:23 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		print_line(t_vm *vm, int *n, int *line, int print_len)
{
	int i;

	i = -1;
	if (print_len == 70)
		while (++i < print_len)
			waddch(vm->visual.win5, vm->bot[vm->last_alive_bot].name[*n + i]);
	else
		mvwprintw(vm->visual.win5, *line, (71 - print_len) / 2, vm->bot[vm->last_alive_bot].name + *n);
	*n += print_len;
	(*line)++;
}

void		check_live_process(t_vm *vm)
{
	t_process	*p;

	if (!(p = vm->process))
		return ;
	if (p->cycles_before_live >= vm->cycle_to_die)
	{
		if (vm->flag_info)
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
			p->num_in_list, p->cycles_before_live, (int)(vm->cycle_to_die));
		kill_process(p, p, vm, 1);
		return (check_live_process(vm));
	}
	while (p && p->next)
	{
		if (p->next->cycles_before_live >= vm->cycle_to_die)
		{
			if (vm->flag_info)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				p->next->num_in_list, p->next->cycles_before_live, (int)(vm->cycle_to_die));
			kill_process(p, p->next, vm, 0);
		}
		else
			p = p->next;
	}
}

void		end_game(t_vm *vm, int fl, int i, int cycle_to_die)
{
	int	n;
	int	line;
	int len_name;

	if (vm->flag_v)
	{
		update_visual_statistics(vm);
		vm->visual.win4 = newwin(10, 75, 50, COLS - 90);
		wbkgd(vm->visual.win4, COLOR_PAIR(2));
		vm->visual.win5 = newwin(8, 71, 51, COLS - 88);
		mvwprintw(vm->visual.win5, 1, (71 - ft_strlen("Game Over")) / 2, "Game Over");
		if (!(vm->last_alive_bot == -1))
		{
			mvwprintw(vm->visual.win5, 3, (71 - ft_strlen("Winner is player №1")) / 2, "Winner is player #%i", vm->last_alive_bot + 1);
			n = 0;
			line = 4;
			wmove(vm->visual.win5, ++line, 0);
			len_name = ft_strlen(vm->bot[vm->last_alive_bot].name);
			while (vm->bot[vm->last_alive_bot].name[n] != '\0')
			{
				if (len_name / 70 > 0)
				{
					print_line(vm, &n, &line, 70);
					len_name -= 70;
				}
				else
					print_line(vm, &n, &line, len_name % 70);

				// if (len_rest = ft_strlen((vm->bot[vm->last_alive_bot].name + n)) > 70)
				// 	print_line(vm->bot[vm->last_alive_bot].name, &n, &line, 1);
				// else
				// 	print_line(vm->bot[vm->last_alive_bot].name, &n, &line, 0);
				
				// if (!((n + 1) % 70) || vm->bot[vm->last_alive_bot].name[n] == '\n')
				// 	wmove(vm->visual.win5, ++line, 1);
				// if (vm->bot[vm->last_alive_bot].name[n] == '\n')
				// {
				// 	n++;
				// 	continue ;
				// }
				// waddch(vm->visual.win5, vm->bot[vm->last_alive_bot].name[n]);
				// n++;
			}
		}
		else
			mvwprintw(vm->visual.win5, 3, 28, "No winner...\n"); 
		refresh();    
		wrefresh(vm->visual.win4);
		wrefresh(vm->visual.win5);	
		wrefresh(vm->visual.win3);	
		// update_curses_win1(vm->map, vm);
		// refresh();  
		// wrefresh(vm->visual.win);
		while (getch() != ' ')
			;		
		
		endwin(); // ?
	}
	// else
	// {
	if (i >= cycle_to_die)
		check_live_process(vm);
	if (fl && vm->num_process)
	{
		if (vm->flag_d)
			ft_print_memory(vm->map, MEM_SIZE, vm, 64);
		else
			ft_print_memory(vm->map,  MEM_SIZE, vm, 32);
		exit(0);
	}
	else if (vm->last_alive_bot == -1)
	{
		ft_printf("Game over!\nNo one survived...\n");
		exit(0);
	}
	else
		ft_printf("Contestant %d, \"%s\", has won !\n", vm->last_alive_bot + 1, vm->bot[vm->last_alive_bot].name);
	
	// }
	// int i = -1;
	// int sum_not_null = 0;
	// int sum_null = 0;
	// while (++i < vm->len_arr)
	// 	if (vm->arr[i] != NULL)
	// 	{
	// 		ft_printf("%i\n", i);
	// 		sum_not_null++;
	// 	}
	// 	else if (vm->arr[i] == NULL)
	// 	{
	// 		// ft_printf("%i\n", i);
	// 		sum_null++;
	// 	}
	// ft_printf("num_processes = %i\n", vm->num_process);
	// ft_printf("sum_not_null = %i\n", sum_not_null);
	// ft_printf("sum_null = %i\n", sum_null);
	// ft_printf("count_enter_kill = %i\n", vm->count_enter_kill);
}

int			cycle_to_die_check(t_vm *vm)
{
	if (vm->live_counter >= NBR_LIVE || vm->nbr_live_checks >= (MAX_CHECKS - 1))
	{
		vm->nbr_live_checks = 0;
		return (CYCLE_DELTA);
	}
	vm->nbr_live_checks++;
	return (0);
}

void		exec_process(t_vm *vm)
{
	unsigned char	bytes[1];
	t_process		*p;

	p = vm->process;
	while (p)
	{
		vm->cur_process = p;
		if (vm->flag_v)
			visual_update_by_process(p, vm);
		p->cycles_before_live++;
		if (!(p->cycles_before_execution))
		{
			if (vm->flag_v)
				random_chat(vm);
			ft_memcpy_overflow(bytes, vm->map, 1, p->location);
			p->command = bytes[0];
			if (bytes[0] >= 0x01 && bytes[0] <= 0x10)
				p->cycles_before_execution = g_op_tab[bytes[0] - 1].cycles_before_execution;
		}
		if (p->cycles_before_execution > 0)
			p->cycles_before_execution--;
		if (!(p->cycles_before_execution))
			apply_operation(p, vm);
		p->location = p->location % MEM_SIZE;
		p = p->next;
	}
}

void		space_waiting(t_vm *vm)
{
	int		c;

	c = getch();
	//nodelay(stdscr, FALSE);
	if (c == ' ')
	{
		nodelay(stdscr, FALSE);
		while (1)
			if (getch() == ' ')
			{
				nodelay(stdscr, TRUE);
				break ;
			}
			else if (c == KEY_EXIT)
				exit(0);
	}
	else if (c == 'd')
		vm->nbr_cycles = 0;
	else if (c == KEY_EXIT)
		exit(0);
	//nodelay(stdscr, TRUE);
}
void		lets_fight(t_vm *vm)
{
	int		i;
	int		tmp;

	i = 0;
	while (vm->process && vm->cycle_to_die > 0)
	{
		if (vm->flag_v)
			space_waiting(vm);
		if (i >= vm->cycle_to_die)
		{
			check_live_process(vm);
			if (!(vm->num_process))
				break ;
			tmp = cycle_to_die_check(vm);
			vm->cycle_to_die -= tmp;
			if (vm->flag_info && vm->cycle_to_die < CYCLE_TO_DIE && tmp)
				ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
			vm->live_counter = 0;
			i = 0;
		}
		if (vm->flag_info)
			ft_printf("It is now cycle %d\n", vm->nbr_all_cycles + 1);
		exec_process(vm);
		i++;
		vm->nbr_all_cycles++;
		if (vm->nbr_cycles != -1 && (!(vm->nbr_cycles) || --vm->nbr_cycles == 0))
		{
			if (vm->process && vm->cycle_to_die > 0)
				end_game(vm, 1, i, vm->cycle_to_die);
			else
				end_game(vm, 0, i, vm->cycle_to_die);
		}
		if (vm->flag_v)
			update_visual_statistics(vm);
	}
	check_live_process(vm);
	tmp = cycle_to_die_check(vm);
	vm->cycle_to_die -= tmp;
	if (vm->flag_info && vm->cycle_to_die < CYCLE_TO_DIE && tmp)
		ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
	if (vm->flag_v)
		update_visual_statistics(vm);
	end_game(vm, 0, i, vm->cycle_to_die);
}
