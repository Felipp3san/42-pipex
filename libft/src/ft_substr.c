/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:00:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/15 21:20:54 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(char const *s, size_t len)
{
	size_t	size;

	size = 0;
	while (size < len && (*(s + size) != '\0'))
		size++;
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	src_size;
	size_t	substr_size;
	size_t	i;

	substr_size = 0;
	src_size = ft_strlen(s);
	if (start < src_size)
		substr_size = ft_strnlen((s + start), len);
	substr = (char *) malloc(substr_size + 1);
	if (substr)
	{
		i = 0;
		while (i < substr_size)
		{
			*(substr + i) = *(s + start + i);
			i++;
		}
		*(substr + i) = '\0';
	}
	return (substr);
}
