/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:49:36 by mwunsch           #+#    #+#             */
/*   Updated: 2019/04/28 00:14:08 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>

int	main()
{
	// system("open -a Terminal.app");
	initscr();                   // Переход в curses-режим/
	// resizeterm(100, 300);
	WINDOW *win = newwin(LINES, COLS - 50, 0, 0);
	WINDOW *win2 = newwin(LINES, 50, 0, COLS - 50); // LINES & COLS - constants that take terminal's size
	// WINDOW *win = newwin(80, 250, 0, 0);
	// WINDOW *win2 = newwin(80, 210, 0, 0);
	box(win, 0, 0);
	box(win2, 0, 0);
	mvwprintw(win, 1, 1, "Hello world!");  // Отображение приветствия в буфер
	mvwprintw(win2, 1, 1, "Hello world!");  // Отображение приветствия в буфер
	// mvprintw(1, 1, "Hello world!");  // Отображение приветствия в буфер
	refresh();                   // Вывод приветствия на настоящий экран
	wrefresh(win);                   // Вывод приветствия на настоящий экран
	wrefresh(win2);                   // Вывод приветствия на настоящий экран
	getch();                     // Ожидание нажатия какой-либо клавиши пользователем
//	raw();                 //Берём управление клавиатурой на себя
	cbreak();                    // Частичный контроль клавы - ctrl+c закончит программу
	while (1)
		; //Просто работаем бесконечно долго
	endwin();                    // Выход из curses-режима. Обязательная команда.
	return 0;
}
