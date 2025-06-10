/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:57:53 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/09 16:14:36 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	quote_check(char c, char *quote)
{
	if (c == '\'' || c == '\"')
	{
		if (*quote == c)
			*quote = 0;
		else if (*quote == 0)
			*quote = c;
	}
}

static size_t	count_words(char const *s, char delimiter)
{
	char	quote;
	int		in_word;
	size_t	word_count;

	quote = 0;
	in_word = 0;
	word_count = 0;
	while (*s)
	{
		quote_check(*s, &quote);
		if (quote || *s != delimiter)
		{
			if (!in_word)
			{
				in_word = 1;
				word_count++;
			}
		}
		else
			in_word = 0;
		s++;
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

int	fill_word_array(char **arr, char const *s, char c)
{
	size_t	i;
	size_t	len;
	size_t	start;
	char	delimiter;

	i = 0;
	start = 0;
	while (i < count_words(s, c))
	{
		delimiter = c;
		while (s[start] == c)
			start++;
		if (s[start] == '\'' || s[start] == '\"')
			delimiter = s[start++];
		len = 0;
		while (s[start + len] && s[start + len] != delimiter)
			len++;
		arr[i] = ft_substr(s, start, len);
		if (!arr[i])
			return (free_all(arr, i - 1), 0);
		start += len + 1;
		i++;
	}
	arr[i] = NULL;
	return (1);
}

char	**ft_split_quotes(char const *s, char c)
{
	char	**arr;

	arr = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!fill_word_array(arr, s, c))
		return (NULL);
	return (arr);
}
