/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 11:31:45 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/29 18:47:59 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		list_init(t_list **lst, t_list **init, t_list **prev, int fd)
{
	if (!*lst)
	{
		if (!(*lst = (t_list *)malloc(sizeof(t_list))))
			return (0);
		(*lst)->next = NULL;
		(*lst)->content = NULL;
		(*lst)->content_size = fd;
	}
	*init = *lst;
	while (*init)
	{
		if ((*init)->content_size == (size_t)fd)
			break ;
		if (!(*init)->next)
		{
			if (!((*init)->next = (t_list *)malloc(sizeof(t_list))))
				return (0);
			(*init)->next->next = NULL;
			(*init)->next->content = NULL;
			(*init)->next->content_size = fd;
		}
		*prev = *init;
		*init = (*init)->next;
	}
	return (1);
}

int		line_init(t_list **lst, size_t (*fls)[5], char **buf, char **line)
{
	if ((*lst)->content)
	{
		(*fls)[3] = 0;
		while (((char *)((*lst)->content))[(*fls)[3]] &&
				((char *)((*lst)->content))[(*fls)[3]] != '\n')
			(*fls)[3]++;
		if ((*fls)[3] != ft_strlen((*lst)->content))
			(*fls)[0] = 1;
		if (!(*line = ft_strnew((*fls)[3])))
			return (0);
		ft_strlcpy(*line, (*lst)->content, (*fls)[3] + 1);
		ft_strlcpy(*buf, (*lst)->content, ft_strlen((*lst)->content) + 1);
	}
	else if (!(*line = ft_strnew(0)))
		return (0);
	return (1);
}

ssize_t	buf_init(ssize_t *ret, size_t (*fls)[5], char **buf, char **line)
{
	char		*new_line;

	while ((*fls)[0] == 0 && (*ret = read((*fls)[2], *buf, BUFF_SIZE)) > 0)
	{
		(*buf)[*ret] = '\0';
		(*fls)[3] = 0;
		while ((*buf)[(*fls)[3]] && (*buf)[(*fls)[3]] != '\n')
			(*fls)[3]++;
		if ((*fls)[3] != (size_t)(*ret))
			(*fls)[1] = 1;
		if (!(new_line = ft_strnew(ft_strlen(*line))))
			return (-1);
		ft_strlcpy(new_line, *line, ft_strlen(*line) + 1);
		ft_strdel(line);
		if (!(*line = ft_strnew(ft_strlen(new_line) + (*fls)[3])))
			return (-1);
		ft_strlcpy(*line, new_line, ft_strlen(new_line) + 1);
		ft_strdel(&new_line);
		ft_strlcat(*line, *buf, ft_strlen(*line) + (*fls)[3] + 1);
		if ((*fls)[1] == 1)
			break ;
	}
	return (*ret);
}

int		ret_init(t_list **lst, size_t (*fls)[5], char **line)
{
	char			*buf;
	ssize_t			ret;
	size_t			len;

	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	if (!line_init(lst, fls, &buf, line))
		return (-1);
	ret = *lst && (*lst)->content ? ft_strlen((*lst)->content) : 0;
	if (buf_init(&ret, fls, &buf, line) == -1)
		return (-1);
	len = ft_strlen(buf) - (*fls)[3];
	ft_strdel((char **)&((*lst)->content));
	if (!((*lst)->content = ft_strnew(len)))
		return (-1);
	ft_strlcpy((*lst)->content, buf + (*fls)[3] + 1 * (len != 0), len + 1);
	ft_strdel(&buf);
	if (!ft_strlen((*lst)->content) || (*fls)[0] + (*fls)[1] == 0)
		ft_strdel((char **)(&((*lst)->content)));
	return (ret > 0 ? 1 : 0);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*lst = NULL;
	t_list			*init;
	t_list			*prev;
	size_t			fls[5];

	prev = NULL;
	if (fd < 0 || !line || BUFF_SIZE <= 0 || !list_init(&lst, &init, &prev, fd))
		return (-1);
	*line = NULL;
	fls[0] = 0;
	fls[1] = 0;
	fls[2] = fd;
	fls[3] = -1;
	if ((fls[4] = (ret_init(&init, &fls, line))) == -1)
		return (-1);
	if (fls[4] || (!fls[4] && ft_strlen(*line) > 0))
		return (1);
	ft_strdel((char **)&(init->content));
	if (prev)
		prev->next = init->next;
	lst = lst == init ? NULL : lst;
	if (init)
		free(init);
	return ((int)fls[4]);
}
