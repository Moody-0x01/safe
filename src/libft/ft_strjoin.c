/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:06:09 by lazmoud           #+#    #+#             */
/*   Updated: 2024/10/24 20:29:06 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	len(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1l;
	size_t	s2l;
	char	*new;
	int		iter;

	if (!s1 || !s2)
		return (NULL);
	s1l = len(s1);
	s2l = len(s2);
	iter = 0;
	new = salloc(s1l + s2l + 1);
	if (!new)
		return (NULL);
	while (s1[iter])
	{
		new[iter] = s1[iter];
		iter++;
	}
	while (s2[iter - s1l])
	{
		new[iter] = s2[iter - s1l];
		iter++;
	}
	new[iter] = 0;
	return (new);
}
