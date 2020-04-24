/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 23:19:54 by zjeyne-l          #+#    #+#             */
/*   Updated: 2020/04/24 15:19:40 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new_ptr;

	if (!size && ptr)
	{
		if (!(new_ptr = (char*)malloc(1)))
			return (NULL);
		ft_memdel(&ptr);
		return (new_ptr);
	}
	if (!(new_ptr = (char*)malloc(size)))
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, size);
		ft_memdel(&ptr);
	}
	return (new_ptr);
}

void	_ft_putstr(const char *str)
{
	int len = 0;
	while (str[len])
		len++;
	write(1, str, len);
}

void	_ft_putstr_endc(const char *str, char c)
{
	int len = 0;
	while (str[len])
		len++;
	write(1, str, len);
	write(1, &c, 1);
}

char	*_ft_strstr(const char *str1, const char *str2)
{
	int i;
	int j;

	i = 0;
	if (!str2[0])
		return ((char*)str1);
	while (str1[i])
	{
		j = 0;
		if (str1[i] == str2[j])
		{
			while (str1[i + j] && (str1[i + j] == str2[j]))
			{
				if (!str2[j + 1])
					return ((char*)&str1[i + j + 1]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
