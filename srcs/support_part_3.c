/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:38:03 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/28 09:45:57 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void	free_line_and_exit_main(char *line, int j)
{
	free(line);
	error_exit(e_no_closing_quote, g_params->num_line, j + 1);
}

void	g_params_init(void)
{
	if (!(g_params = (t_params *)malloc(sizeof(t_params))))
		error_exit(e_malloc_error, 0, 0);
	g_params->labels_all = NULL;
	g_params->num_line = 1;
}

int	ft_atoi_registers(const char *str)
{
	int		res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (res >= 100)
			return (0);
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

void		vars_init(t_header **header, t_main **main, char **line, int *i)
{
	*i = 0;
	*line = NULL;
	(*header)->prog_name = NULL;
	(*header)->comment = NULL;
	(*main)->num_of_op = -1;
	(*main)->size_of_op = 0;
	(*main)->labels = NULL;
	(*main)->next = NULL;
	(*main)->args[0] = 0;
	(*main)->args[1] = 0;
	(*main)->args[2] = 0;
}

void	free_line_and_exit_header(char *line, int j)
{
	free(line);
	error_exit(e_no_closing_quote, g_params->num_line, j + 1);
}

