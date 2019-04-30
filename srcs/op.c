/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/04/28 01:38:33 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

t_op	g_op_tab[NUM_OF_OPS] =
{
	{"live", 1, {T_DIR}, 1, 10, 0, 4, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, 1, 4, 1},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, 1, 4, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 4, 1},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 4, 1},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6 , 1, 4, 1},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, 1, 4, 1},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, 1, 4, 1},
	{"zjmp", 1, {T_DIR}, 9, 20, 0, 2, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 1, 2, 0},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 1, 2, 0},
	{"fork", 1, {T_DIR}, 12, 800, 0, 2, 0},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, 1, 4, 1},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, 1, 2, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, 0, 2, 0},
	{"aff", 1, {T_REG}, 16, 2, 1, 4, 0}
};
