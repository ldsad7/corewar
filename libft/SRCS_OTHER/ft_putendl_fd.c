/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 14:43:10 by bsprigga          #+#    #+#             */
/*   Updated: 2018/11/30 21:31:07 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char const *s, int fd)
{
	int		len;
	char	n;

	if (!s)
		return ;
	len = ft_strlen((char *)s);
	write(fd, s, len);
	n = '\n';
	write(fd, &n, 1);
}
