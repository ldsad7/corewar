/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 18:30:21 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:16:42 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		clear_all_exit(int option)
{
	g_f->curr_flags ? free(g_f->curr_flags) : 1;
	g_f->str ? free(g_f->str) : 1;
	g_f->str = NULL;
	free(g_f);
	if (option == -1)
		exit(-1);
}

t_format	*g_f_new(void)
{
	t_format *tmp;

	if (!(tmp = (t_format *)ft_memalloc(sizeof(t_format))))
		clear_all_exit(-1);
	if (!(tmp->curr_flags = ft_strnew(5)))
		clear_all_exit(-1);
	tmp->width_value = -1;
	tmp->prec_value = -1;
	tmp->size = L_NONE;
	tmp->type = '\0';
	tmp->str = NULL;
	tmp->null_c_len = -1;
	tmp->type_p = 0;
	tmp->big_f = 0;
	return (tmp);
}

char		*make_size_string(char *str)
{
	char	*res;

	if (!(res = ft_strnew(ft_strlen(str))))
		clear_all_exit(-1);
	ft_strcpy(res, str);
	return (res);
}

char		*ft_itoa_base_unsigned(unsigned long long n, int base)
{
	char				*res;
	int					i;
	unsigned long long	n_ini;

	n_ini = n;
	i = 1;
	while ((n_ini = n_ini / base))
		i++;
	res = (char *)ft_strnew(sizeof(*res) * i);
	if (!res)
		return (0);
	while ((--i) > -1)
	{
		if (n % base > 9)
			res[i] = (n % base) + 'A' - 10;
		else
			res[i] = (n % base) + '0';
		n /= base;
	}
	return (res);
}
