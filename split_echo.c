/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 20:32:21 by zjeyne-l          #+#    #+#             */
/*   Updated: 2020/04/21 17:37:32 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


int		ft_word(char const *str, int *idx)
{
	int i = 0;
	while (str[i] && str[i] == '$' && (!str[i + 1] || str[i + 1] == '$'))
		i++;
	*idx = i;

	int word = 0;
	while (str[i])
	{
		if (str[i] != '$' && (!str[i + 1] || str[i + 1] == '$'))
			word++;

		// if (str[i] == '$' && (!str[i + 1] || str[i + 1] == '$'))
		// 	word++;

		i++;
	}
	return (word);
}

char	**ft_strsplit_echo(char const *str)
{
	char **ar;
	int i;
	int id = 0;

	int word = ft_word(str, &i);
	if (word <= 0)
		return (NULL);

	ar = (char**)malloc(sizeof(char*) * (word + 1));

	int l = i;
	while (str[i++])
	{
		if (str[i] == '$' || !str[i])
		{
			ar[id] = (char*)malloc(sizeof(char) * (i - l + 1));
			int j = l - 1;
			while (++j < i)
			{
				ar[id][j - l] = str[j];
			}
			ar[id][j] = '\0';

			l = i;
			id++;
		}

		// if (str[i] != '$' && (!str[i + 1] || str[i + 1] == '$'))
		// {
		// 	ar[id] = (char*)malloc(sizeof(char) * (i - l + 2));
		// 	int j = l - 1;
		// 	while (++j <= i)
		// 	{
		// 		ar[id][j - l] = str[j];
		// 	}
		// 	ar[id][j - l] = '\0';

		// 	i++;
		// 	while (str[i] && str[i] == '$' && (!str[i + 1] || str[i + 1] == '$'))
		// 		i++;

		// 	l = i;
		// 	id++;
		// }
		// i++;
	}
	ar[word] = NULL;

	return (ar);
}
