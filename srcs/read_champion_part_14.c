/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_14.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:20:52 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/28 01:11:16 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

unsigned int	find_program_size(t_main *main)
{
	unsigned int	size;

	size = 0;
	while (main)
	{
		size += main->size_of_op;
		main = main->next;
	}
	return (size);
}

void		reverse_labels_list(t_list **list)
{
	t_list *previous;
	t_list *current;
	t_list *next;

	if (!list || !(*list))
		return ;
	previous = *list;
	if ((current = previous->next) == NULL)
		return ;
	previous->next = NULL;
	while (current->next)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	current->next = previous;
	*list = current;
}

void		dump_champion(t_header *header, t_main *main)
{
	t_list			*labels;
	unsigned int	sum;
	int				num_arg;

	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %u bytes\n", find_program_size(main));
	ft_printf("Name : \"%s\"\n", header->prog_name);
	ft_printf("Comment : \"%s\"\n\n", header->comment);
	sum = 0;
	while (main)
	{
		reverse_labels_list(&(main->labels));
		labels = main->labels;
		while (labels)
		{
			ft_printf("%-11u:    %s:\n", sum, labels->content);
			labels = labels->next;
		}
		ft_printf("%-5u(%-3u) :        %-10s",
		sum, main->size_of_op, g_op_tab[main->num_of_op].name);
		num_arg = -1;
		while (++num_arg < g_op_tab[main->num_of_op].num_of_args)
			ft_printf("%-18s", main->old_args[num_arg]);
		write(1, "\n                    ", 21);
		ft_printf("%-10d", g_op_tab[main->num_of_op].num);
		num_arg = -1;
		while (++num_arg < g_op_tab[main->num_of_op].num_of_args)
			ft_printf("%-18s", main->args[num_arg]);
		write(1, "\n", 1);
		sum += main->size_of_op;
		main = main->next;
		if (main)
			write(1, "\n", 1);
	}
}
