/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:39:14 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/20 20:24:10 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	word_count;
	size_t	char_count;
	size_t	str_len;

	if (!s)
		return (0);
	i = 0;
	char_count = 0;
	word_count = 0;
	str_len = ft_strlen(s);
	while (i < str_len)
	{
		if (s[i] != c)
		{
			if (char_count == 0)
				word_count++;
			char_count++;
		}
		else
			char_count = 0;
		i++;
	}
	return (word_count);
}

static void	free_all(char **arr, int size)
{
	while (size >= 0)
	{
		free(arr[size]);
		size--;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	len;
	size_t	start;

	arr = (char **) malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	start = 0;
	while (i < count_words(s, c))
	{
		while (s[start] == c)
			start++;
		len = 0;
		while (s[start + len] && s[start + len] != c)
			len++;
		arr[i] = ft_substr(s, start, len);
		if (!arr[i])
			return (free_all(arr, i - 1), NULL);
		start += len;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
