/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:50:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/15 20:50:45 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup_str;
	size_t	src_size;
	size_t	i;

	src_size = ft_strlen(s);
	dup_str = (char *) malloc (src_size + 1);
	if (dup_str)
	{
		i = 0;
		while (i < src_size)
		{
			*(dup_str + i) = *(s + i);
			i++;
		}
		*(dup_str + i) = '\0';
	}
	return (dup_str);
}
