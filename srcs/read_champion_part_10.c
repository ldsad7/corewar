/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_10.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:16:36 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/28 01:11:03 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

static unsigned long long	any_to_ten(char *from, int base_from)
{
	int					len;
	unsigned long long	ret;
	unsigned long long	pow_of_base;

	len = ft_strlen(from);
	pow_of_base = 1;
	ret = 0;
	while (--len != -1)
	{
		if (from[len] <= 'F' && from[len] >= 'A')
			ret += (10 + from[len] - 'A') * pow_of_base;
		else if (from[len] <= 'f' && from[len] >= 'a')
			ret += (10 + from[len] - 'a') * pow_of_base;
		else
			ret += (from[len] - '0') * pow_of_base;
		pow_of_base *= base_from;
	}
	return (ret);
}

static void					recursive_func(char **to, int index,
									int base_to_fl[2], unsigned long long ten)
{
	if (index < 0)
		return ;
	recursive_func(to, index - 1, base_to_fl, ten / base_to_fl[0]);
	if (ten % base_to_fl[0] > 9)
		(*to)[index] = 'A' + base_to_fl[1] * 32 - 10 + ten % base_to_fl[0];
	else
		(*to)[index] = '0' + ten % base_to_fl[0];
}

static char					*get_base(unsigned long long ten,
										int base_to, int fl)
{
	char				*to;
	int					new_len;
	int					base_to_fl[2];
	unsigned long long	copy;

	new_len = 1;
	copy = ten;
	while (copy / base_to)
	{
		copy /= base_to;
		new_len++;
	}
	if (!(to = (char *)malloc(sizeof(char) * (new_len + 1))))
		return (NULL);
	to[new_len] = '\0';
	base_to_fl[0] = base_to;
	base_to_fl[1] = fl;
	recursive_func(&to, new_len - 1, base_to_fl, ten);
	return (to);
}

char						*change_base(char *from, int base_from,
											int base_to, int fl)
{
	unsigned long long	ten;

	ten = any_to_ten(from, base_from);
	return (get_base(ten, base_to, fl));
}
