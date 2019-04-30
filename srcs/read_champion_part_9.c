/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_9.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 16:48:42 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/30 00:58:31 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

int			sum_correction(int *used_label, unsigned int *sum, int declared_label)
{
	*used_label = 1;
	if (!declared_label)
		*sum = 0;
	else
	{
		*sum = -(*sum);
		return (1);
	}
	return (0);
}

unsigned int	bias_for_label(char *label, t_main *iter_main,
								t_main *main, int arg_num)
{
	unsigned int	sum;
	int				declared_label;
	int				used_label;

	sum = 0;
	declared_label = 0;
	used_label = 0;
	while (iter_main)
	{
		find_label(iter_main, &declared_label, label);
		if (iter_main->args_row_num == main->args_row_num)
		{
			if (sum_correction(&used_label, &sum, declared_label))
				break ;
		}
		if (declared_label && used_label)
			break ;
		else if ((declared_label && !used_label) || (!declared_label && used_label))
			sum += iter_main->size_of_op;
		iter_main = iter_main->next;
	}
	if (!declared_label)
		error_exit(e_no_label, main->args_row_num, main->args_symbols_nums[arg_num] + 1);
	return (sum);
}

void		replace_label_for_direct(t_main **main, int arg_num, t_main *top)
{
	char			*label;
	unsigned int	byte_bias;

	if (!(label = ft_strsub((*main)->args[arg_num], 2,
				ft_strlen((*main)->args[arg_num]) - 2)))
		error_exit(e_malloc_error, 0, 0);
	byte_bias = bias_for_label(label, top, *main, arg_num);
	replace_label(byte_bias, main, arg_num);
	free(label);
}

void		replace_label_for_indirect(t_main **main, int arg_num, t_main *top)
{
	char	*label;
	int		byte_bias;

	if (!(label = ft_strsub((*main)->args[arg_num], 1,
				ft_strlen((*main)->args[arg_num]) - 1)))
		error_exit(e_malloc_error, 0, 0);
	byte_bias = bias_for_label(label, top, *main, arg_num);
	replace_label(byte_bias, main, arg_num);
	free(label);
}

void		replace_labels_with_numbers(t_main **main)
{
	t_main		*top;
	int			arg_num;

	top = *main;
	while (*main)
	{
		arg_num = 0;
		while (arg_num < g_op_tab[(*main)->num_of_op].num_of_args)
		{
			if (ft_strlen((*main)->args[arg_num]) > 1
				&& (*main)->args[arg_num][0] == DIRECT_CHAR
				&& (*main)->args[arg_num][1] == LABEL_CHAR)
				replace_label_for_direct(main, arg_num, top);
			else if ((*main)->args[arg_num][0] == LABEL_CHAR)
				replace_label_for_indirect(main, arg_num, top);
			else
				(*main)->old_args[arg_num] = (*main)->args[arg_num];
			arg_num++;
		}
		*main = (*main)->next;
	}
	*main = top;
}
