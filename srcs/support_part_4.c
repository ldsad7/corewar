/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:38:03 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/29 22:55:55 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void	error_exit7(int value, int num_line, int symbol)
{
	if (value == e_no_exec_code)
		exit(ft_fprintf(2, "Error: there is no exec code in .asm file [%d:%d]\n",
						num_line, symbol));
	exit(0);
}

void	error_exit6(int value, int num_line, int symbol)
{
	if (value == e_two_labels_in_row)
		exit(ft_fprintf(2, "Error: two labels in row [%d:%d]\n",
						num_line, symbol));
	else if (value == e_open_error)
		exit(ft_fprintf(2, "Error: attempting to open file failed\n"));
	else if (value == e_malloc_error)
		exit(ft_fprintf(2, "Error: Malloc returned NULL\n"));
	else if (value == e_no_opening_quote)
		exit(ft_fprintf(2, "Error: no opening \" after instruction [%d:%d]\n",
						num_line, symbol));
	else if (value == e_no_closing_quote)
		exit(ft_fprintf(2, "Error: no closing \" after instruction [%d:%d]\n",
						num_line, symbol));
	else if (value == e_name_too_long)
		exit(ft_fprintf(2, "Error: program name is too long [%d:%d] (Max length 128)\n",
						num_line, symbol));
	else if (value == e_no_arguments_for_corewar)
	{ // переписать usage
		ft_fprintf(2, "Error: no arguments for ./corewar program\n");
		ft_fprintf(2, "Usage: ./vm_champs/corewar [-d N -s N -v N | -b --stealth | -n --stealth] [-a] <champion1.cor> <...>\n\
    -a        : Prints output from \"aff\" (Default is to hide it)\n\
#### TEXT OUTPUT MODE ##########################################################\n\
    -d N      : Dumps memory after N cycles then exits (64 bit format)\n\
    -dump N   : Dumps memory after N cycles then exits (32 bit format)\n\
    -info     : show full info on operations\n\
    -v        : visualization\n\
#### NCURSES OUTPUT MODE #######################################################\n\
	-n        : Ncurses output mode\n\
################################################################################\n");
	}
	error_exit7(value, num_line, symbol);
}
