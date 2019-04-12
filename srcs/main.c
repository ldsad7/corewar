/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 01:17:40 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/12 15:34:17 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

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



// void	read_arguments(char **line, int *j, t_main **new)
// {
	
// }



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
