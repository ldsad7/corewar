/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:01:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/29 02:33:33 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isnumeric(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (!(*str))
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!(*str))
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
