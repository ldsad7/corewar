/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/12 18:57:48 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
**	free(str) needed to compensate ft_strsub() calls which is an argument to
**	this function in parse_operation()
*/

int		find_op(char *str)
{
	int	i;

	i = 0;
	while (i < NUM_OF_OPS)
	{
		if (ft_strcmp(g_op_tab[i].name, str) == 0)
			return (i + 1);
		i++;
	}
	free(str);
	return (0);
}

static void	skip_empty_and_comment_lines(char **line, int *j, int fd_input,
										t_main **new)
{
	char	*line_fd;

	while (!((*line)[*j]) || (*line)[*j] == COMMENT_CHAR ||
	(*line)[*j] == ALT_COMMENT_CHAR)
	{
		if (!(line_fd = NULL) && get_next_line(fd_input, &line_fd) <= 0)
			free_line_and_exit_main(*line, *new, *j);
		else
		{
			free(*line);
			*line = line_fd;
			*j = 0;
			(*new)->num_line++;
			while ((*line)[*j] && ft_strchr(" \n\t", (*line)[*j]))
				(*j)++;
		}
	}
}

/*
**	row 27-41 - while loop needed to skip all rows that are empty or start with
**	comment char
*/

void		read_command(char **line, int *j, int fd_input, t_main **new)
{
	int		i;
	char	*tmp;

	while ((*line)[*j] && ft_strchr(" \n\t", (*line)[*j]))
		(*j)++;
	skip_empty_and_comment_lines(line, j, fd_input, new);
	i = *j;
	while ((*line)[i] && (*line)[i] != ' ') // redundant part? because in above else block same while is executed
		i++;
	if (!((*line)[i]))
	{
		if (find_op(ft_strsub(*line, i, i - *j))) // should be !find_op(ft_strsub(*line, i, j - i)) !!!!!!!!!!!!!!!!!!!!!
			error_exit(e_no_operation, (*new)->num_line, *j);
		else
			error_exit(e_not_enough_arguments, (*new)->num_line, i);
	}
	else
	{
		if (!(tmp = ft_strsub(*line, *j, i - *j)))
			error_exit(e_malloc_error, (*new)->num_line, *j);
		if (!((*new)->num_of_op = find_op(tmp)))
			error_exit(e_no_operation, (*new)->num_line, i);
		free(tmp);
		// read_arguments(line, &j, &new);
	}
}
