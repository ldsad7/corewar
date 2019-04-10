/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 01:17:40 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/11 02:58:46 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	error_exit(int value)
{
	if (value == e_num_args_not_one)
		exit(ft_fprintf(2, "Number of given arguments is not one"));
	else if (value == e_incorrect_file)
		exit(ft_fprintf(2, "Incorrect file argument"));
	else if (value == e_open_error)
		exit(ft_fprintf(2, "Incorrect opening of file"));
	else if (value == e_malloc_error)
		exit(ft_fprintf(2, "Malloc error"));
}

// void	champion_file_parsing(int fd, t_header **header)
// {
// 	char		*line;

// 	line = NULL;
// 	while (get_next_line(fd, &line) > 0)
// 	{
// 		//
// 	}
// }

int		main(int argc, char *argv[])
{
	int			fd;
	t_header	*header;

	if (argc != 2)
		error_exit(e_num_args_not_one);
	if (ft_strcmp(argv[1] + ft_strlen(argv[1]) - 2, ".s"))
		error_exit(e_incorrect_file);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		error_exit(e_open_error);
	if (!(header = (t_header *)malloc(sizeof(t_header))))
		error_exit(e_malloc_error);
	// champion_file_parsing(fd, &header);
}