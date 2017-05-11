/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 18:58:18 by garouche          #+#    #+#             */
/*   Updated: 2017/04/29 12:03:06 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wordlen(const char *s, int a)
{
	int i;

	i = 0;
	if (s == NULL)
		return (1);
	while (s[a] && s[a] > 32)
	{
		i++;
		a++;
	}
	return (i);
}

int		ft_nbword(const char *s)
{
	size_t word;
	size_t i;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && s[i] <= 32)
			i++;
		if (s[i] > 32)
			word++;
		while (s[i] && s[i] > 32)
			i++;
	}
	return (word);
}

char	**ft_strsplit_white(char const *s)
{
	int		a;
	size_t	n;
	char	**str;

	a = 0;
	n = 0;
	if (s == NULL)
		return (NULL);
	str = (char**)malloc(sizeof(char*) * (ft_nbword(s) + 2));
	if (str == NULL)
		return (NULL);
	while (s[a])
	{
		if (s[a] > 32)
		{
			str[n] = ft_strsub(s, a, ft_wordlen(s, a));
			a = a + ft_wordlen(s, a);
			n++;
		}
		if (s[a])
			a++;
	}
	str[n] = 0;
	return (str);
}
