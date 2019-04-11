/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 01:17:40 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/11 14:01:32 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_list	*read_fd(int fd)
{
	char	*line;
	t_list	*list;
	int		read_row_status;

	line = NULL;
	if ((read_row_status = get_next_line(fd, &line)) > 0)
		if (!(list = ft_lstnew(line, ft_strlen(line))))
			error_exit(e_malloc_error);
	if (read_row_status == 0)
		error_exit(e_empty_file);
	while ((read_row_status = get_next_line(fd, &line) > 0))
		ft_lstadd(&list, ft_lstnew(line, ft_strlen(line)));
	if (read_row_status < 0)
		error_exit(e_error_reading_file);
	ft_lstreverse(&list);
	// while (list)
	// {
	// 	ft_putstr(list->content);
	// 	ft_putstr("\n");
	// 	list = list->next;
	// }
	return (list);
}

void	champion_file_parsing(int fd, t_list **list, t_header **header)
{
	*header = NULL;
	*list = read_fd(fd);
	// while (get_next_line(fd, &line) > 0)
	// {
	// 	if (!(row = ft_lstnew(line, ft_strlen(line))))
	// 		error_exit(e_malloc_error);
	// }
}

int		main(int argc, char *argv[])
{
	int			fd;
	t_header	*header;
	t_list		*list;

	if (argc != 2)
		error_exit(e_num_args_not_one);
	if (ft_strcmp(argv[1] + ft_strlen(argv[1]) - 2, ".s"))
		error_exit(e_incorrect_file);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		error_exit(e_open_error);
	if (!(header = (t_header *)malloc(sizeof(t_header))))
		error_exit(e_malloc_error);
	champion_file_parsing(fd, &list, &header);
}
