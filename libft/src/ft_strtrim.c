/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:24:22 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/18 21:40:52 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char const *set, char ch)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimm_str;
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (in_set(set, s1[start]))
		start++;
	while (in_set(set, s1[end - 1]) && end > start)
		end--;
	trimm_str = (char *) malloc((end - start) + 1);
	if (trimm_str)
	{
		i = 0;
		while (i < (end - start))
		{
			trimm_str[i] = s1[start + i];
			i++;
		}
		trimm_str[i] = '\0';
	}
	return (trimm_str);
}
