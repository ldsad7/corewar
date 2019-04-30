/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_7.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:41:34 by mwunsch           #+#    #+#             */
/*   Updated: 2019/04/30 05:31:21 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		print_hex(unsigned char hex)
{
	char	*tab;

	tab = "0123456789abcdef";
	ft_putchar(tab[hex / 16]);
	ft_putchar(tab[hex % 16]);
}

static void	make_hexs(unsigned char *line, int base)
{
	int		i;

	i = -1;
	while (++i < base)
	{
		print_hex(line[i]);
		ft_putchar(' ');
	}
}

void		ft_print_memory(const void *addr, int size, t_vm *vm, int base)
{
	unsigned char	*tmp;
	int				curline;

	curline = 0;
	tmp = (unsigned char*)addr;
	if (base)
		while (curline * base < size)
		{
			ft_printf("0x%04x : ", curline * base);
			make_hexs(tmp, base);
			write(1, "\n", 1);
			tmp += base;
			curline++;
		}
	else
	{
		curline = -1;
		while (++curline < size)
		{
			if (curline == vm->process->location)
			{
				ft_putstr("\x1b[46m");
				print_hex(tmp[curline]);
				ft_putstr("\x1b[0m");
			}
			else
				print_hex(tmp[curline]);
			ft_putchar(' ');
		}
	}
}

void		init_chat(t_vm *vm)
{
	vm->visual.win3 = newwin(10, 75, 40, COLS - 90);
	box(vm->visual.win3, 0, 0);
	mvwprintw(vm->visual.win3, 1, 1, "Chating..."); 
	refresh();    
	wrefresh(vm->visual.win3);
}

void		random_chat(t_vm *vm)
{
	srand(time(NULL));
	if (rand() % 15 == 0)
		chatting(vm, vm->bot[rand() % (vm->num_bots)].name, rand() % 8 + 1);
}

int		visual_statistics_print_ustr(WINDOW *win, char *str, int line)
{
	int		n;

	wmove(win, line, 1);
	n = 0;
	while (str[n] != '\0')
	{
		if (!((n + 1) % 70) || str[n] == '\n')
			wmove(win, ++line, 1);
		if (str[n] == '\n')
		{
			n++;
			continue ;
		}
		waddch(win, str[n]);
		n++;
	}
	// wmove(win, ++line, 1);
	return (line + 1);
}

void		chatting(t_vm *vm, char *name, int fl)
{
	int		line;
	
	wmove(vm->visual.win3, 3, 1);
	wclrtobot(vm->visual.win3);
	line = visual_statistics_print_ustr(vm->visual.win3, name, 3) + 1;
	// wmove(vm->visual.win3, line, 1);
	// wclrtoeol(vm->visual.win3);
	box(vm->visual.win3, 0, 0);
	refresh();
	wrefresh(vm->visual.win3);
	if (fl == 1)
		visual_statistics_print_ustr(vm->visual.win3, "\"Nobody can hurt me without my permition.\"", line);
	else if (fl == 2)
		visual_statistics_print_ustr(vm->visual.win3, "\"I'm still alive!\"", line);
	else if (fl == 3)
		visual_statistics_print_ustr(vm->visual.win3, "\"Fighting for peace is like screwing for virginity.\"", line);
	else if (fl == 4)
		visual_statistics_print_ustr(vm->visual.win3,
		"\"Fighting with him was like trying to solve a crossword and realizing there's no right answer.\"", line);
	else if (fl == 5)
		visual_statistics_print_ustr(vm->visual.win3, "\"اك أمل دائماً لمن يحارب.. أما من يست فلا أمل ل\"", line);
	else if (fl == 6)
		visual_statistics_print_ustr(vm->visual.win3, "\"I find your lack of faith disturbing.\"", line);
	else if (fl == 7)
		visual_statistics_print_ustr(vm->visual.win3, "\"I’ve got a bad feeling about this.\"", line);
	else if (fl == 8)
		visual_statistics_print_ustr(vm->visual.win3, "\"Death is the solution to all problems.\"", line);
	else if (fl == 9)
		visual_statistics_print_ustr(vm->visual.win3, "\"I have no idea what i'm doing...\"", line);
		// int i = -1;
	// while (++i < 200)
	// 	waddch(vm->visual.win3, ' ');	
	wclrtobot(vm->visual.win3);
	box(vm->visual.win3, 0, 0);
	refresh();
	wrefresh(vm->visual.win3);
}

void		visual_statistics_print_bot_name(t_vm *vm)
{
	int		i;
	// int		n;

	vm->visual.start_point_statistics = 5;
	i = -1;
	wmove(vm->visual.win2, vm->visual.start_point_statistics, 1);
	while (++i < vm->num_bots)
	{
		if (!vm->bot[i].weapon)
			break ;
		if (i == 0)
		// n = 0;
		// while (vm->bot[i].name[n] != '\0')
		// {
			if (i == 0)
				vm->visual.start_point_statistics = visual_statistics_print_ustr(vm->visual.win2, "(1)(RED)", vm->visual.start_point_statistics);
			if (i == 1)
				vm->visual.start_point_statistics = visual_statistics_print_ustr(vm->visual.win2, "(2)(GREEN)", vm->visual.start_point_statistics);
			if (i == 2)
				vm->visual.start_point_statistics = visual_statistics_print_ustr(vm->visual.win2, "(3)(BLUE)", vm->visual.start_point_statistics);
			if (i == 3)
				vm->visual.start_point_statistics = visual_statistics_print_ustr(vm->visual.win2, "(4)(YELLOW)", vm->visual.start_point_statistics);

			vm->visual.start_point_statistics = visual_statistics_print_ustr(vm->visual.win2, vm->bot[i].name, vm->visual.start_point_statistics);
			// if (!(n + 1) % 73 || vm->bot[i].name[n] == '\n')
			// 	wmove(vm->visual.win2, ++vm->visual.start_point_statistics, 1);
			// if (vm->bot[i].name[n] == '\n')
			// {
			// 	n++;
			// 	continue ;
			// }
			// waddch(vm->visual.win2, vm->bot[i].name[n]);
			// n++;
		// }
		// wmove(vm->visual.win2, vm->visual.start_point_statistics, 1);
	}
	++vm->visual.start_point_statistics;
}

void		visual_statistics_print_dump_counter(t_vm *vm, int *line)
{
	(*line)++;
	if (vm->nbr_cycles == -1) 
		mvwprintw(vm->visual.win2, (*line)++, 1, "Dump counter: unavailable");
	else
		mvwprintw(vm->visual.win2, (*line)++, 1, "Dump counter: %d", vm->nbr_cycles);
}

void		init_visual_statistics(t_vm *vm)
{
	vm->visual.win2 = newwin(35, 75, 5, COLS - 90);
	box(vm->visual.win2, 0, 0);
	mvwprintw(vm->visual.win2, 1, 1, "Fight statistics:"); 
	mvwprintw(vm->visual.win2, 4, 1, "%d fighters:", vm->num_bots);
	visual_statistics_print_bot_name(vm);
	update_visual_statistics(vm);
}

void		update_visual_statistics(t_vm *vm)
{
	int		line;
	int		n;

	line = vm->visual.start_point_statistics;
	wmove(vm->visual.win2, line, 1);
	wclrtobot(vm->visual.win2);
	box(vm->visual.win2, 0, 0);
	mvwprintw(vm->visual.win2, line++, 1, "Processes in fight %d", vm->num_process);
	visual_statistics_print_dump_counter(vm, &line);
	line++;
	if (vm->flag_a)
		mvwprintw(vm->visual.win2, line++, 1, "Aff operation: %c", vm->aff_value);
	else
		mvwprintw(vm->visual.win2, line++, 1, "Aff operation: unavailable");


	line++;
	mvwprintw(vm->visual.win2, line++, 1, "Cycles to die %d left", vm->cycle_to_die);
	line++;
	mvwprintw(vm->visual.win2, line++, 1, "Cycle %d", vm->nbr_all_cycles);
	line++;
	mvwprintw(vm->visual.win2, line++, 1, "Last said that he is not dead yet:");
	n = 0;
	wmove(vm->visual.win2, line, 1);
	if  (vm->last_alive_bot == -1) 
		mvwprintw(vm->visual.win2, line, 1, "...silence of the Lambs");
	else 
		visual_statistics_print_ustr(vm->visual.win2, vm->bot[vm->last_alive_bot].name, line);
	refresh();
	wrefresh(vm->visual.win2);
}

void		visual_update_by_process(t_process *p, t_vm *vm)
{
	p->location = modulo_mem_size(p->location);
	wmove(vm->visual.win, p->location_prev / 64, p->location_prev % 64 * 3);
	// wattron(vm->visual.win, COLOR_PAIR(p->master + 5));
	wattron(vm->visual.win, COLOR_PAIR(p->master + 5));
	waddch(vm->visual.win, TAB[vm->map[p->location_prev] / 16]);
	waddch(vm->visual.win, TAB[vm->map[p->location_prev] % 16]);
	wattroff(vm->visual.win, COLOR_PAIR(p->master + 5));
	// waddch(vm->visual.win, ' ');
	wmove(vm->visual.win, modulo_mem_size(p->location) / 64, p->location % 64 * 3);
	wattron(vm->visual.win, COLOR_PAIR(p->master + 1));
	waddch(vm->visual.win, TAB[vm->map[p->location] / 16]);
	waddch(vm->visual.win, TAB[vm->map[p->location] % 16]);
	wattroff(vm->visual.win, COLOR_PAIR(p->master + 1));
	// waddch(vm->visual.win, ' ');
	p->location_prev = p->location;
	refresh();                   // Вывод приветствия на настоящий экран
	wrefresh(vm->visual.win);                   // Вывод приветствия на настоящий экран
}

void		initialise_color(void)
{
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_RED);	// 1 цвет, bot
	init_pair(2, COLOR_WHITE, COLOR_GREEN);	// 2 цвет  
	init_pair(3, COLOR_WHITE, COLOR_BLUE);	// 3 цвет 
	init_pair(4, COLOR_WHITE, COLOR_MAGENTA);	// 4 цвет 
	init_pair(5, COLOR_RED, COLOR_BLACK);	// 5 цвет, process - красные символы на чёрном фоне
	init_pair(6, COLOR_GREEN, COLOR_BLACK);	// 6 цвет  
	init_pair(7, COLOR_BLUE, COLOR_BLACK);	// 7 цвет 
	init_pair(8, COLOR_YELLOW, COLOR_BLACK); //8 цвет 


	init_pair(9, COLOR_BLACK, COLOR_WHITE); //test цвет 

}

void		init_visualization(t_vm *vm)
{
	initscr();                   // Переход в curses-режим
	initialise_color();
	vm->visual.win = newwin(MEM_SIZE / 64 * 3, 64 * 3, 2, 2);
	refresh();                   // Вывод приветствия на настоящий экран
	cbreak();                    // Частичный контроль клавы - ctrl+c закончит программу
	keypad(stdscr, TRUE);   //Включаем режим чтения функциональных клавиш
    noecho();               //Выключаем отображение вводимых символов, нужно для getch()
    nodelay(stdscr, TRUE);
	// halfdelay(1);         //Устанавливаем ограничение по времени ожидания getch() в 10 сек
	wmove(vm->visual.win, 0, 0);
}

void		init_varibles(int *bot_nr, int *count, int *i)
{
	*bot_nr = 0;
	*count = 0;
	*i = 0;
}

void		print_curses_put_hex(t_vm *vm, unsigned char *addr, int i)
{
	waddch(vm->visual.win, TAB[addr[i] / 16]);
	waddch(vm->visual.win, TAB[addr[i] % 16]);
	waddch(vm->visual.win, ' ');
}

void		print_curses_new_line(t_vm *vm, int i)
{
	waddch(vm->visual.win, '\n');
	wmove(vm->visual.win, i / 64, 0);
}

void		print_curses(unsigned char *addr, t_vm *vm)
{
	int		i;
	int		bot_nr;
	int		count;
	
	init_varibles(&bot_nr, &count, &i);
	init_visualization(vm);
	while (i < MEM_SIZE)
	{
		if (bot_nr < vm->num_bots && i == MEM_SIZE / vm->num_bots * bot_nr)
		{
			count = vm->bot[bot_nr].weapon_size;
			wattron(vm->visual.win, COLOR_PAIR(bot_nr + 5));		
		}
		print_curses_put_hex(vm, addr, i);
		if (--count == 0)
		{
			wattroff(vm->visual.win, COLOR_PAIR(bot_nr + 5));
			bot_nr++;
		}
		i++;
		if (i % 64 == 0)
			print_curses_new_line(vm, i);
	
	}
	refresh();                   // Вывод приветствия на настоящий экран
	wrefresh(vm->visual.win);                   // Вывод приветствия на настоящий экран
}

// void		update_curses_win1(unsigned char *addr, t_vm *vm)
// {
// 	int		i;
// 	i = 0;
// 	while (i < MEM_SIZE)
// 	{
// 		print_curses_put_hex(vm, addr, i);
// 		i++;
// 		if (i % 64 == 0)
// 			print_curses_new_line(vm, i);
// 	}
// }

/*
** visualiser 1.0 edition
*/

// void		print_curses(unsigned char *addr, int size, t_vm *vm)
// {
// 	int				i;
// 	int				a;
// 	char			*tab;

// 	a = 0;
// 	tab = "0123456789abcdef";
// 	initscr();                   // Переход в curses-режим
// 	start_color();
// 	init_pair(1, COLOR_RED, COLOR_BLACK);	// 1 цвет в палитре - красные символы на чёрном фоне
// 	init_pair(2, COLOR_GREEN, COLOR_BLACK);	// 2 цвет  
// 	init_pair(3, COLOR_BLUE, COLOR_BLACK);	// 3 цвет 
// 	init_pair(4, COLOR_YELLOW, COLOR_BLACK); // 4 цвет 
// 	WINDOW *win = newwin(MEM_SIZE / 64 * 3, 64 * 3, 2, 2);
// 	WINDOW *win2 = newwin(LINES, COLS, 1, 1);
// 	box(win2, 0, 0);
// 	refresh();                   // Вывод приветствия на настоящий экран
// 	cbreak();                    // Частичный контроль клавы - ctrl+c закончит программу
// 	wmove(win, 0, 0);
// 	i = -1;
// 	t_process *p = vm->process;
// 	while (++i < size)
// 	{
// 		p = vm->process;
// 		while (p)
// 		{
// 			if (i == p->location)
// 			{
// 				wattron(win, COLOR_PAIR(p->master + 1));
// 				waddch(win, tab[addr[i] / 16]);
// 				waddch(win, tab[addr[i] % 16]);
// 				wattroff(win, COLOR_PAIR(p->master + 1));
// 				break ;
// 			}
// 			p = p->next;
// 		}
// 		if (!p)
// 		{
// 			waddch(win, tab[addr[i] / 16]);
// 			waddch(win, tab[addr[i] % 16]);
// 		}
// 		waddch(win, ' ');	
// 		a++;
// 		if (a == 64)
// 		{
// 			waddch(win, '\n');
// 			wmove(win, i / 64, 0);
// 			a = 0;
// 		}
// 	}
// 		refresh();                   // Вывод приветствия на настоящий экран
// 		wrefresh(win);                   // Вывод приветствия на настоящий экран
// }