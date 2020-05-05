/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 23:27:08 by zjeyne-l          #+#    #+#             */
/*   Updated: 2020/05/05 19:23:22 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


int 	ft_word_count(char const *s, int *i, int *id)
{
	int j;
	int words;

	j = 0;
	words = 0;
	*i = 0;
	*id = 0;
	while (s[*i] && (s[*i] == ' ' || s[*i] == '\n' || s[*i] == '\t' || s[*i] == '\v' || s[*i] == '\f' || s[*i] == '\r' || s[*i] == '\b' || s[*i] == '\a'))
		*i += 1;
	while (s[j])
	{
		if ((s[j] != ' ' || s[j] != '\n' || s[j] != '\t' || s[j] != '\v' || s[j] != '\f' || s[j] != '\r' || s[j] != '\b' || s[j] != '\a')
				&& ((s[j + 1] == ' ' || s[j + 1] == '\n' || s[j + 1] == '\t' || s[j + 1] == '\v' || s[j + 1] == '\f' || s[j + 1] == '\r' || s[j + 1] == '\b' || s[j + 1] == '\a')
					|| !s[j + 1]))
			words++;
		j++;
	}
	return (words);
}

int 	ft_sl(char *str)
{
	int len;

	len = 0;
	while (str[len] && (str[len] != ' ' || str[len] == '\n' || str[len] == '\t' || str[len] == '\v' || str[len] == '\f' || str[len] == '\r' || str[len] == '\b' || str[len] == '\a'))
		len++;
	return (len);
}

void 	ft_word_input(char const *s, int start, int end, char *ar)
{
	int i;

	i = 0;
	while (start < end)
	{
		ar[i] = s[start];
		start++;
		i++;
	}
	ar[i] = '\0';
}

char	**ft_free(char **ar, int id)
{
	while (--id > 0)
		free(ar[id]);
	ar[id] = NULL;
	return (ar);
}

char	**ft_strsplit_whitespaces(char const *s)
{
	int i;
	int l;
	int id;
	char **ar;

	if (!s)
		return (NULL);
	if (!(ar = (char**)malloc(sizeof(char*) * (ft_word_count((char*)s, &i, &id) + 1))))
		return (NULL);
	l = i;
	while (s[i++])
	{
		if ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\v' || s[i] == '\f' || s[i] == '\r' || s[i] == '\b' || s[i] == '\a') || !s[i])
		{
			if (!(ar[id] = (char *)malloc(ft_sl((char *)&s[l]) + 1)))
				return (ft_free(ar, id));
			ft_word_input((char *)s, l, i, ar[id++]);
			while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\v' || s[i] == '\f' || s[i] == '\r' || s[i] == '\b' || s[i] == '\a')
				i++;
			l = i;
		}
	}
	ar[id] = NULL;
	return (ar);
}

void	ft_strsplit_free(char **split)
{
	int i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
