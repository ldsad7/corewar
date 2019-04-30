/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/29 23:27:49 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void	label_or_op_end_init(t_indexes *indexes, char *line,
							int label_or_op_start)
{
	indexes->label_or_op_end = label_or_op_start;
	indexes->label_or_op_start = label_or_op_start;
	if (line[indexes->label_or_op_end] == LABEL_CHAR)
		error_exit(e_empty_label, g_params->num_line, label_or_op_start + 1);
	while (line[indexes->label_or_op_end] &&
	ft_strchr(LABEL_CHARS, line[indexes->label_or_op_end]))
		indexes->label_or_op_end++;
	if (!(line[indexes->label_or_op_end]) ||
		line[indexes->label_or_op_end] == COMMENT_CHAR ||
		line[indexes->label_or_op_end] == ALT_COMMENT_CHAR)
		error_no_oper_no_args(line, label_or_op_start, indexes->label_or_op_end);
}

void	add_label_to_labels_all(char *label)
{
	char	*tmp;
	t_list	*tmp_list;

	if (!(tmp = ft_strdup(label)))
		error_exit(e_malloc_error, 0, 0);
	if (!(tmp_list = ft_lstnew(tmp, ft_strlen(tmp))))
		error_exit(e_malloc_error, 0, 0);
	if (g_params->labels_all)
		ft_lstadd(&(g_params->labels_all), tmp_list);
	else
		g_params->labels_all = tmp_list;
}

int		parse_label(t_main *new, char **line, t_indexes *indexes)
{
	char	*tmp;
	t_list	*tmp_list;

	if (!(tmp = ft_strsub(*line, indexes->label_or_op_start,
	indexes->label_or_op_end - indexes->label_or_op_start)))
		error_exit(e_malloc_error, 0, 0);
	if (!(tmp_list = ft_lstnew(tmp, ft_strlen(tmp))))
		error_exit(e_malloc_error, 0, 0);
	check_valid_label(tmp_list->content, indexes->label_or_op_start,
	e_check_in_all_labels);
	if (new->labels)
		ft_lstadd(&(new->labels), tmp_list);
	else
		new->labels = tmp_list;
	add_label_to_labels_all(tmp_list->content);
	return (check_after_label(line, indexes));
}

int		parse_operation_gnl_iter(char **line, int *label_or_op_start,
								int fd_input)
{
	*label_or_op_start = 0;
	check_slash_zero(fd_input, ft_strlen(*line) + 1);
	free(*line);
	if (get_next_line(fd_input, line) <= 0)
		error_exit(e_no_operation, g_params->num_line + 1, 0);
	check_slash_zero(fd_input, ft_strlen(*line) + 1);
	g_params->num_line++;
	while ((*line)[*label_or_op_start] &&
	ft_strchr(" \t", (*line)[*label_or_op_start]))
		(*label_or_op_start)++;
	if (!((*line)[*label_or_op_start]) || (*line)[*label_or_op_start] ==
	COMMENT_CHAR || (*line)[*label_or_op_start] == ALT_COMMENT_CHAR)
		return (1);
	return (0);
}

void	parse_operation(char **line, int label_or_op_start,
						int fd_input, t_main **main)
{
	t_main		*new;
	t_indexes	*indexes;

	new = new_op_setup(main);
	indexes = indexes_init(label_or_op_start);
	while (!indexes->quit)
	{
		if (indexes->launch_gnl)
			if (parse_operation_gnl_iter(line, &label_or_op_start, fd_input))
				continue ;
		label_or_op_end_init(indexes, *line, label_or_op_start);
		if ((*line)[indexes->label_or_op_end] == LABEL_CHAR)
		{
			if (parse_label(new, line, indexes))
			{
				read_command(line, indexes->label_or_op_start, fd_input, &new);
				indexes->quit = 1;
			}
		}
		else
		{
			read_command(line, indexes->label_or_op_start, fd_input, &new);
			indexes->quit = 1;
		}
	}
	free(indexes);
	update_main(main, &new);
}
