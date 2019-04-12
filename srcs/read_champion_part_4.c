/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/12 15:33:23 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		find_op(char *str)
{
	int		i;

	i = 0;
	while (i < NUM_OF_OPS)
	{
		if (!ft_strcmp(g_op_tab[i].name, str))
			return (i + 1);
		i++;
	}
	return (0);
}

void	read_command(char **line, int *j, int fd_input, t_main **new)
{
	char	*line_fd;
	int		i;
	char	*tmp;

	while ((*line)[*j] && ft_strchr(" \n\t", (*line)[*j]))
		(*j)++;
	while (!((*line)[*j]) || (*line)[*j] == COMMENT_CHAR || (*line)[*j] == ALT_COMMENT_CHAR)
	{
		if (!(line_fd = NULL) && get_next_line(fd_input, &line_fd) <= 0)
			free_line_and_exit_main(*line, *new, *j);
		else
		{
			*j = 0;
			free(*line);
			*line = line_fd;
			(*new)->num_line++;
			while ((*line)[*j] && ft_strchr(" \n\t", (*line)[*j]))
				(*j)++;
		}
	}
	i = *j;
	while ((*line)[i] && (*line)[i] != ' ')
		i++;
	if (!((*line)[i]))
	{
		if (find_op(ft_strsub(*line, i, i - *j)))
			error_exit(e_no_operation, (*new)->num_line, *j);
		else
			error_exit(e_not_enoguh_arguments, (*new)->num_line, i);
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

void	check_label(char *str, int i, t_main *main)
{
	int		j;

	j = 0;
	while (str[j])
	{
		if (!ft_strchr(LABEL_CHARS, str[j]))
			error_exit(e_incorrect_symbol_in_label, main->num_line, i + j);
		j++;
	}
}

void	parse_operation(char **line, int i, int fd_input, t_main **main)
{
	t_main	*new;
	int		j;
	char	*tmp;

	if (((*main)->num_of_op))
	{
		if (!(new = (t_main *)malloc(sizeof(t_main))))
			error_exit(e_malloc_error, (*main)->num_line, i);
		new->num_line = (*main)->num_line;
	}
	else
		new = *main;
	j = i;
	if ((*line)[j] == ':')
		error_exit(e_empty_label, (*main)->num_line, i);
	while ((*line)[j] && (*line)[j] != ' ' && (*line)[j] != ':')
		j++;
	if (!((*line)[j]))
	{
		if (find_op(ft_strsub(*line, i, j - i)))
			error_exit(e_no_operation, (*main)->num_line, i);
		else
			error_exit(e_not_enoguh_arguments, (*main)->num_line, j);
	}
	else if ((*line)[j] == ':')
	{
		if (!(new->label = ft_strsub(*line, i, j - i)))
			error_exit(e_malloc_error, (*main)->num_line, j);
		check_label(new->label, i, *main);
		j++;
		read_command(line, &j, fd_input, &new);
	}
	else if ((*line)[j] == ' ')
	{
		new->label = NULL;
		if (!(tmp = ft_strsub(*line, i, j - i)))
			error_exit(e_malloc_error, (*main)->num_line, i);
		if (!(new->num_of_op = find_op(tmp)))
			error_exit(e_no_operation, (*main)->num_line, j);
		free(tmp);
		// read_arguments(line, &j, &new);
	}
}
