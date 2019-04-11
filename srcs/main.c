/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 01:17:40 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/12 02:55:12 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		startswith(char *str, char *start, int num)
{
	int		i;

	if (ft_strlen(start) > ft_strlen(str)
		|| num > (int)ft_strlen(start) || num < 0)
		return (0);
	i = 0;
	while (start[i] && i < num)
	{
		if (start[i] != str[i])
			return (0);
		i++;
	}
	return (1);
}

int		endswith(char *str, char *end, int num)
{
	int		i;
	int		j;

	if (ft_strlen(end) > ft_strlen(str)
		|| num > (int)ft_strlen(end) || num < 0)
		return (0);
	i = ft_strlen(str) - 1;
	j = ft_strlen(end) - 1;
	while (j > -1 && num > -1)
	{
		if (end[j] != str[i])
			return (0);
		i--;
		j--;
		num--;
	}
	return (1);
}

// void	check_last_slash_n(t_list *list)
// {
// 	while (list->next)
// 		list = list->next;
// 	while (*((char *)(list->content)) && *((char *)list->content + 1))
// 		list->content = list->content + 1;
// 	if (*((char *)list->content) != '\n')
// 		error_exit(e_last_instruction_not_slash_n);
// }

// t_list	*read_fd(int fd)
// {
// 	char	*buf;
// 	t_list	*list;
// 	int		read_row_status;

// 	if (!(buf = ft_strnew(BUFF_SIZE)))
// 		error_exit(e_malloc_error);
// 	list = NULL;
// 	if ((read_row_status = read(fd, buf, BUFF_SIZE)) > 0)
// 		if (!(list = ft_lstnew(buf, ft_strlen(buf))))
// 			error_exit(e_malloc_error);
// 	if (read_row_status == 0)
// 		error_exit(e_empty_file);
// 	while (read_row_status)
// 	{
// 		if (!(buf = ft_strnew(BUFF_SIZE)))
// 			error_exit(e_malloc_error);
// 		if ((read_row_status = read(fd, buf, BUFF_SIZE)) > 0)
// 			ft_lstadd(&list, ft_lstnew(buf, ft_strlen(buf)));
// 	}
// 	if (read_row_status < 0)
// 		error_exit(e_error_reading_file);
// 	ft_lstreverse(&list);
// 	check_last_slash_n(list);
// 	// while (list)
// 	// {
// 	// 	ft_putstr(list->content);
// 	// 	ft_putstr("\n");
// 	// 	list = list->next;
// 	// }
// 	return (list);
// }

// t_list		*list;
// list = read_fd(fd_input);

void	check_errors_name(char *line, int i, int j, t_header *header)
{
	if (!(line[j]))
	{
		if (header->prog_name)
			error_exit(e_repeating_name_instruction, header->num_line, i + 1);
		else
			error_exit(e_no_name_after_name_command, header->num_line, j + 1);
	}
	if (line[j] != '"')
		error_exit(e_no_opening_quote, header->num_line, j + 1);
	if (header->prog_name)
		error_exit(e_repeating_name_instruction, header->num_line, i + 1);
}

void	check_errors_comment(char *line, int i, int j, t_header *header)
{
	if (!(line[j]))
	{
		if (header->comment)
			error_exit(e_repeating_comment_instruction, header->num_line, i + 1);
		else
			error_exit(e_no_comment_after_comment_command, header->num_line, j + 1);
	}
	if (line[j] != '"')
		error_exit(e_no_opening_quote, header->num_line, j + 1);
	if (header->comment)
		error_exit(e_repeating_comment_instruction, header->num_line, i + 1);
}

void	check_length_name(int name_i, int j, t_header *header)
{
	if (name_i >= PROG_NAME_LENGTH)
				error_exit(e_name_too_long, header->num_line, j + 1);
}

void	check_length_comment(int comment_i, int j, t_header *header)
{
	if (comment_i >= COMMENT_LENGTH)
				error_exit(e_comment_too_long, header->num_line, j + 1);
}

char	*name_malloc(void)
{
	char	*name;

	if (!(name = (char *)malloc(sizeof(char) * (PROG_NAME_LENGTH + 1))))
		error_exit(e_malloc_error, 0, 0);
	return (name);
}

char	*comment_malloc(void)
{
	char	*comment;

	if (!(comment = (char *)malloc(sizeof(char) * (COMMENT_LENGTH + 1))))
		error_exit(e_malloc_error, 0, 0);
	return (comment);
}

void	free_line_and_exit_header(char *line, t_header *header, int j)
{
	free(line);
	error_exit(e_no_closing_quote, header->num_line, j + 1);
}

char	*name_filling(char **line, int *j, int fd_input, t_header **header)
{
	char	*name;
	int		name_i;
	char	*line_fd;

	name = name_malloc();
	name_i = 0;
	while ((*line)[*j] != '"')
	{
		if (!((*line)[*j]) && !(line_fd = NULL) && get_next_line(fd_input, &line_fd) <= 0)
			free_line_and_exit_header(*line, *header, *j);
		else if (!((*line)[*j]))
		{
			*j = 0;
			free(*line);
			*line = line_fd;
			check_length_name(name_i, *j, *header);
			(*header)->num_line++;
			name[name_i++] = '\n';
			continue ;
		}
		check_length_name(name_i, *j, *header);
		name[name_i++] = (*line)[(*j)++];
	}
	name[name_i] = '\0';
	return (name);
}

char	*comment_filling(char **line, int *j, int fd_input, t_header **header)
{
	char	*comment;
	int		comment_i;
	char	*line_fd;

	comment = comment_malloc();
	comment_i = 0;
	while ((*line)[*j] != '"')
	{
		if (!((*line)[*j]) && !(line_fd = NULL) && get_next_line(fd_input, &line_fd) <= 0)
			free_line_and_exit_header(*line, *header, *j);
		else if (!((*line)[*j]))
		{
			*j = 0;
			free(*line);
			*line = line_fd;
			check_length_comment(comment_i, *j, *header);
			(*header)->num_line++;
			comment[comment_i++] = '\n';
			continue ;
		}
		check_length_comment(comment_i, *j, *header);
		comment[comment_i++] = (*line)[(*j)++];
	}
	comment[comment_i] = '\0';
	return (comment);
}

void	parse_name(char **line, int i, int fd_input, t_header **header)
{
	int		j;

	j = i + 5;
	while ((*line)[j] && ft_strchr(" \n\t", (*line)[j]))
		j++;
	check_errors_name(*line, i, j, *header);
	++j;
	(*header)->prog_name = name_filling(line, &j, fd_input, header);
	j++;
	while ((*line)[j] && ft_strchr(" \n\t", (*line)[j]))
		j++;
	if ((*line)[j] && (*line)[j] != COMMENT_CHAR && (*line)[j] != ALT_COMMENT_CHAR)
		error_exit(e_invalid_instruction, (*header)->num_line, j + 1);
}

void	parse_comment(char **line, int i, int fd_input, t_header **header)
{
	int		j;

	j = i + 8;
	while ((*line)[j] && ft_strchr(" \n\t", (*line)[j]))
		j++;
	check_errors_comment(*line, i, j, *header);
	++j;
	(*header)->comment = comment_filling(line, &j, fd_input, header);
	j++;
	while ((*line)[j] && ft_strchr(" \n\t", (*line)[j]))
		j++;
	if ((*line)[j] && (*line)[j] != COMMENT_CHAR && (*line)[j] != ALT_COMMENT_CHAR)
		error_exit(e_invalid_instruction, (*header)->num_line, j + 1);
}

void	parse_instruction(char **line, int i, int fd_input, t_header **header) {
	if (startswith(*line + i, ".name", 5))
		parse_name(line, i, fd_input, header);
	else if (startswith(*line + i, ".comment", 8))
		parse_comment(line, i, fd_input, header);
	else
		error_exit(e_invalid_instruction, (*header)->num_line, i + 1);
}

void	vars_init(t_header **header, t_main **main, char **line, int *i)
{
	*i = 0;
	*line = NULL;
	(*header)->magic = 0; // NB: заменить
	(*header)->prog_name = NULL;
	(*header)->prog_size = 0;
	(*header)->comment = NULL;
	(*header)->num_line = 1;
	(*main)->num_of_op = 0;
	(*main)->size_of_op = 0;
	(*main)->label = NULL;
	(*main)->next = NULL;
	(*main)->num_line = 0;
}

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

void	free_line_and_exit_main(char *line, t_main *main, int j)
{
	free(line);
	error_exit(e_no_closing_quote, main->num_line, j + 1);
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

// void	read_arguments(char **line, int *j, t_main **new)
// {
	
// }

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

void	check_prog_name_and_comment_existence(t_header *header, int i)
{
	if (!(header->prog_name))
		error_exit(e_no_name, header->num_line, i + 1);
	else if (!(header->comment))
		error_exit(e_no_comment, header->num_line, i + 1);
}

void	parsing_line_by_line(int fd_input, t_header **header, t_main **main)
{
	char		*line;
	int			i;

	vars_init(header, main, &line, &i);
	while (get_next_line(fd_input, &line) > 0)
	{
		i = 0;
		while (line[i] && ft_strchr(" \n\t", line[i]))
			i++;
		if (!(line[i]) || line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT_CHAR)
			;
		else if (line[i] == '.')
			parse_instruction(&line, i, fd_input, header);
		else if (!((*header)->prog_name) || !((*header)->comment))
			check_prog_name_and_comment_existence(*header, i);
		else
		{
			if (!((*main)->num_line))
				(*main)->num_line = (*header)->num_line;
			parse_operation(&line, i, fd_input, main);
		}
		free(line);
		(*header)->num_line++;
		(*main)->num_line = (*main)->num_line + ((*main)->num_line != 0);
	}
	check_prog_name_and_comment_existence(*header, i);
}

void	champion_file_parsing(char *filename)
{
	int			fd_input;
	t_header	*header;
	t_main		*main;

	if ((fd_input = open(filename, O_RDONLY)) < 0)
		error_exit(e_open_error, 0, 0);
	if (!(header = (t_header *)malloc(sizeof(t_header))))
		error_exit(e_malloc_error, 0, 0);
	if (!(main = (t_main *)malloc(sizeof(t_main))))
		error_exit(e_malloc_error, 0, 0);
	parsing_line_by_line(fd_input, &header, &main);
}

int		main(int argc, char *argv[])
{
	if (argc != 2)
		error_exit(e_num_args_not_one, 0, 0);
	if (!endswith(argv[1], ".s", 2))
		error_exit(e_incorrect_s_file, 0, 0);
	champion_file_parsing(argv[1]);
	// printf("%s\n", (*header)->prog_name);
	// printf("%s\n", (*header)->comment);
}
