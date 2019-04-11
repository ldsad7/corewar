/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 01:17:40 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/11 16:06:55 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	check_last_slash_n(t_list *list)
{
	while (list->next)
		list = list->next;
	while (*((char *)(list->content)) && *((char *)list->content + 1))
		list->content = list->content + 1;
	if (*((char *)list->content) != '\n')
		error_exit(e_last_instruction_not_slash_n);
}

t_list	*read_fd(int fd)
{
	char	*buf;
	t_list	*list;
	int		read_row_status;

	if (!(buf = ft_strnew(BUFF_SIZE)))
		error_exit(e_malloc_error);
	list = NULL;
	if ((read_row_status = read(fd, buf, BUFF_SIZE)) > 0)
		if (!(list = ft_lstnew(buf, ft_strlen(buf))))
			error_exit(e_malloc_error);
	if (read_row_status == 0)
		error_exit(e_empty_file);
	while (read_row_status)
	{
		if (!(buf = ft_strnew(BUFF_SIZE)))
			error_exit(e_malloc_error);
		if ((read_row_status = read(fd, buf, BUFF_SIZE)) > 0)
			ft_lstadd(&list, ft_lstnew(buf, ft_strlen(buf)));
	}
	if (read_row_status < 0)
		error_exit(e_error_reading_file);
	ft_lstreverse(&list);
	check_last_slash_n(list);
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
