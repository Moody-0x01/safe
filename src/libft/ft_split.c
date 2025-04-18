/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:24:10 by lazmoud           #+#    #+#             */
/*   Updated: 2024/10/24 18:11:14 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	words_len;
	int	word_len;
	int	i;

	i = 0;
	words_len = 0;
	word_len = 0;
	while (s[i])
	{
		if (c == s[i])
		{
			if (word_len)
			{
				words_len++;
				word_len = 0;
			}
			i++;
			continue ;
		}
		word_len++;
		i++;
	}
	if (word_len > 0)
		words_len++;
	return (words_len);
}

static int	length_until(char const *s, int idx, char c)
{
	int	len;

	len = 0;
	while (c != s[idx + len] && s[idx + len])
		len++;
	return (len);
}

static char	**ft_split_private(char **vec,
	char const *s, char c, size_t vec_idx)
{
	int		wlength;
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (s[i])
	{
		while (c == s[i] && s[i])
			i++;
		wlength = length_until(s, i, c);
		if (wlength > 0)
		{
			vec[vec_idx] = salloc_check(salloc(wlength + 1));
			while (k < wlength && s[i])
				vec[vec_idx][k++] = s[i++];
			vec[vec_idx++][k] = 0;
			k = 0;
		}
	}
	vec[vec_idx] = NULL;
	return (vec);
}

char	**ft_split(char const *s, char c)
{
	char	**vec;

	vec = salloc_check(salloc(sizeof(char *) * (count_words(s, c) + 1)));
	if (!vec)
		return (NULL);
	return (ft_split_private(vec, s, c, 0));
}
