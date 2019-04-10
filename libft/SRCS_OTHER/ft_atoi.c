/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 17:41:56 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/02 11:18:14 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	unsigned long int	res;
	int					is_negative;

	is_negative = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			is_negative = -1;
		str++;
	}
	res = 0;
	while (*str >= 48 && *str <= 57)
	{
		if (((res == 922337203685477580 && (*str - '0') > 7) || \
		res > 922337203685477580) && is_negative == 1)
			return (-1);
		else if (((res == 922337203685477580 && (*str - '0') > 8) || \
		res > 922337203685477580) && is_negative == -1)
			return (0);
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * is_negative);
}
