/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 01:17:40 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/29 22:20:07 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

t_params *g_params;

int		main(int argc, char *argv[])
{
	g_params_init();
	if (argc != 2 && argc != 3)
		error_exit(e_num_args_not_one_or_two, 0, 0);
	if (argc == 2)
	{
		if (!endswith(argv[1], ".s"))
			error_exit(e_incorrect_s_file, 0, 0);
		champion_file_parsing(argv[1], 0);
	}
	else
	{
		if (!ft_strcmp(argv[1], "-disass"))
			disassemble(argv[2]);
		else if (!ft_strcmp(argv[1], "-a"))
		{
			if (!endswith(argv[2], ".s"))
				error_exit(e_incorrect_s_file, 0, 0);
			else
				champion_file_parsing(argv[2], 1);
		}
		else
			error_exit(e_incorrect_flag, 0, 0);
	}
}
