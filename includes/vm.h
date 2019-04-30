/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:23:14 by mwunsch           #+#    #+#             */
/*   Updated: 2019/04/29 23:11:06 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <ncurses.h>

#define TAB 			"0123456789abcdef"

typedef struct			s_process
{
	int					location; // позиция
	int					location_prev; // позиция на предыдущем ходу
	int					location_arg; // нужно при чтении команд
	int					carry; // флаг carry
	int					reg[REG_NUMBER]; // регистры
	int					cycles_before_live; // количество циклов после последнего выполнения операция live
	int					cycles_before_execution; // количество циклов, оставшихся до исполнения команды
	int					master; // игрок, породивший каретку
	int					command; // номер команды (может измениться)
	int					num_in_list; // номер процесса в листе, как если бы мы ничего не удаляли из него
	struct s_process	*next; // лист, поэтому next
}						t_process;

typedef struct			s_bot
{
	char				*name; // имя
	char				*comment; // коммент
	unsigned int		weapon_size; // размер исполняемого кода
	unsigned char		*weapon; // исполняемый код
}						t_bot;

typedef struct			s_visual
{
	WINDOW				*win; // arena (map)
	WINDOW				*win2; // statistics
	WINDOW				*win3; // chat
	WINDOW				*win4; // game over window border
	WINDOW				*win5; // game over window inner
	int					start_point_statistics;
}						t_visual;

typedef struct			s_vm
{
	t_bot				bot[MAX_PLAYERS]; // боты
	int					num_bots; // количество игроков
	unsigned char		*map; // карта
	t_process			*process; // каретки
	t_process			*cur_process; // current кареткa
	int					nbr_all_cycles; // количество прошедших с начала игры циклов
	int					live_counter; // количество выполненных операций live за последний период длиной в cycles_to_die
	int					cycle_to_die; // длительность периода до проверки
	int					last_alive_bot; // игрок, указанный в этой переменной, последним подал сигнал live
	int					nbr_live_checks; // количество проведенных проверок live
	int					flag_a; // -a flag for aff operationFight statistics:
	int					aff_value; // for aff operation
	int					flag_d; // -d flag - 64b
	int					flag_v; // -v flag for visualiser
	int					flag_info; // -info flag for debug printing
	int					nbr_cycles; // for -dump flag
	int					num_process; // количество процессов (нужна только для визуализации), хотя также и для corewar
	int					all_processes; // переменная для присвоения номера каждому процессу
	t_visual			visual;
	// int					len_arr;
	// t_process			*arr[10000];
	int					count_enter_kill;
}						t_vm;

int						get_next_bot_index(t_vm *vm);
void					add_bot(char *file, int i, t_vm *vm);
int						skip_flags(char **argv, int i);
void					num_bots_checker(t_vm *vm);
void					add_bots(int argc, char **argv, t_vm *vm);
t_process				*new_process(int location, int master, t_vm *vm);
t_process				*add_process(int location, int master, t_process *prev, t_vm *vm);
void					bots_to_map(t_vm *vm);
void					get_flag_dump(char *flag, t_vm *vm);
void					get_flag_n(char *num, char *file, t_vm *vm);
int						get_flags(int argc, char **argv, int i, t_vm *vm);
void					flags_checker(int argc, char **argv, t_vm *vm);
void					parsing(int argc, char **argv, t_vm *vm);
void            		error_exit(int x, int a, int b);
void					ft_print_memory(const void *addr, int size, t_vm *vm, int fl);
void					bots_checker(t_vm *vm);
void					kill_process(t_process *prev, t_process *cur,
						t_vm *vm, int first);
void					lets_fight(t_vm *vm);
void					ft_memcpy_overflow(const void *dst, const void *src, int n, int start);
void					apply_operation(t_process *process, t_vm *vm);
void					process_operation(int num_of_op, t_process *process, t_vm *vm);
void					ld_operation(int num_of_op, t_process *process, t_vm *vm, int args[4]);
void					add_sub_operations(int num_of_op, t_process *process, t_vm *vm);
void					and_or_xor_operations(int num_of_op, t_process *process, t_vm *vm, int args[4]);
int						read_indirect_argument(t_process *process, t_vm *vm);
void					ldi_operation(int num_of_op, t_process *process, t_vm *vm, int args[4]);
void					fork_operation(int num_of_op, t_process *process, t_vm *vm);
void					aff_operation(t_process *process, t_vm *vm);
void					sti_operation(int num_of_op, t_process *process, t_vm *vm, int args[4]);
void					zjmp_operation(int num_of_op, t_process *process, t_vm *vm);
void					st_operation(t_process *process, t_vm *vm, int args[4]);
void					live_operation(int num_of_op, t_process *process, t_vm *vm);
int						write_registry_argument(t_process *process, t_vm *vm, int value);
int						read_registry_argument(t_process *process, t_vm *vm, int *read_value);
void					read_correct_arguments(int num_of_op, t_process *process, t_vm *vm, int args[4]);
int						else_branch(unsigned char bytes[4], int num_arg, int (*args)[4], int num_of_op);
void					print_curses(unsigned char *addr, t_vm *vm);
void					visual_update_by_process(t_process *p, t_vm *vm);
void					init_chat(t_vm *vm);
void					chatting(t_vm *vm, char *name, int fl);
void					random_chat(t_vm *vm);
void					init_visual_statistics(t_vm *vm);
void					update_visual_statistics(t_vm *vm);
void					print_hex(unsigned char hex);
void					error_exit6(int value, int num_line, int symbol);
void					update_curses_win1(unsigned char *addr, t_vm *vm);
int						modulo_mem_size(int value);

#endif
