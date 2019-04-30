/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/28 08:52:52 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void	update_main(t_main **main, t_main **new)
{
	if (*new == *main)
		(*new)->next = NULL;
	else
		(*new)->next = *main;
	*main = *new;
}

void	check_op(t_main *new, int op_start, int op_end, char *line)
{
	char	*tmp;

	if (!(tmp =
		ft_strsub(line, op_start, op_end - op_start)))
		error_exit(e_malloc_error, g_params->num_line, op_start);
	if (!(new->num_of_op = find_op(tmp)))
		error_exit(e_no_operation, g_params->num_line, op_start);
	new->num_of_op--;
	free(tmp);
}

int		find_op(char *str)
{
	int	i;

	i = 0;
	while (i < NUM_OF_OPS)
	{
		if (!ft_strcmp(g_op_tab[i].name, str))
			return (i + 1);
		i++;
	}
	free(str);
	return (0);
}

static void	skip_empty_and_comment_lines(char **line, int *op_start,
										int fd_input)
{
	char	*line_fd;

	line_fd = NULL;
	while ((*line)[*op_start] && ft_strchr(" \t", (*line)[*op_start]))
		(*op_start)++;
	while (!((*line)[*op_start]) || (*line)[*op_start] == COMMENT_CHAR ||
	(*line)[*op_start] == ALT_COMMENT_CHAR)
	{
		if (!((*line)[*op_start]))
			check_slash_zero(fd_input, ft_strlen(line_fd) + 1);
		free(*line);
		if (!(line_fd = NULL) && get_next_line(fd_input, &line_fd) <= 0)
			error_exit(e_no_operation_after_label,
						g_params->num_line, *op_start + 1);
		*line = line_fd;
		*op_start = 0;
		g_params->num_line++;
		while ((*line)[*op_start] && ft_strchr(" \t", (*line)[*op_start]))
			(*op_start)++;
	}
	if (line_fd)
		check_slash_zero(fd_input, ft_strlen(line_fd) + 1);
	else
		check_slash_zero(fd_input, ft_strlen(*line) + 1);
}

void		read_command(char **line, int op_start, int fd_input, t_main **new)
{
	int		op_end;

	skip_empty_and_comment_lines(line, &op_start, fd_input);
	op_end = op_start;
	while ((*line)[op_end] && ft_strchr(ALPHABET, (*line)[op_end]))
		op_end++;
	if (!((*line)[op_end]) || (*line)[op_end] == COMMENT_CHAR
		|| (*line)[op_end] == ALT_COMMENT_CHAR)
		error_no_oper_no_args(*line, op_start, op_end);
	else
	{
		check_op(*new, op_start, op_end, *line);
		read_arguments(*line, op_end, new, fd_input);
	}
}
