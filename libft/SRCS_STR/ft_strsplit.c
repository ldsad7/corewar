/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:28:07 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/02 20:56:16 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

static size_t	count_words(const char *s, char c)
{
	int		trigger;
	size_t	word;

	trigger = 0;
	word = 0;
	while (*s)
	{
		if (*s != c && trigger == 0)
		{
			word++;
			trigger = 1;
		}
		if (*s == c && trigger == 1)
			trigger = 0;
		s++;
	}
	return (word);
}

static int		found_word_end(const char *str, char c)
{
	size_t	end;

	end = 1;
	while (str[end] != '\0' && str[end] != c)
		end++;
	return (end);
}

static char		**word_split(char **res, char const *s, char c, size_t k)
{
	size_t	word_num;
	size_t	border;
	char	*word;

	word_num = 0;
	while (word_num < k)
	{
		if (*s != c)
		{
			border = found_word_end(s, c);
			if ((word = ft_strsub(s, 0, border)) == NULL)
			{
				while (word_num-- > 0)
					free(res[word_num]);
				free(res);
				return (NULL);
			}
			res[word_num++] = word;
			s += border;
			continue;
		}
		s++;
	}
	res[k] = NULL;
	return (res);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**res;
	size_t		k;

	if (!s)
		return (0);
	k = count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (k + 1));
	if (res == NULL)
		return (NULL);
	res = word_split(res, s, c, k);
	return (res);
}
