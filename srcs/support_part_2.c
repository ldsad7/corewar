/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:38:03 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/28 01:11:23 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

int		startswith(char *str, char *start)
{
	int		i;

	if (ft_strlen(start) > ft_strlen(str))
		return (0);
	i = 0;
	while (start[i])
	{
		if (start[i] != str[i])
			return (0);
		i++;
	}
	return (1);
}

int		endswith(char *str, char *end)
{
	int		i;
	int		j;

	if (ft_strlen(end) > ft_strlen(str))
		return (0);
	i = ft_strlen(str) - 1;
	j = ft_strlen(end) - 1;
	while (j > -1)
	{
		if (end[j] != str[i])
			return (0);
		i--;
		j--;
	}
	return (1);
}

char	*name_comment_malloc(int len)
{
	char	*name;

	if (!(name = (char *)malloc(sizeof(char) * (len + 1))))
		error_exit(e_malloc_error, 0, 0);
	return (name);
}

void	check_length_name(int name_i, int symbol)
{
	if (name_i >= PROG_NAME_LENGTH)
		error_exit(e_name_too_long, g_params->num_line, symbol + 1);
}

void	check_length_comment(int comment_i, int symbol)
{
	if (comment_i >= COMMENT_LENGTH)
		error_exit(e_comment_too_long, g_params->num_line, symbol + 1);
}
