/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:32:12 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/18 22:32:23 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;
	size_t	found;
	char	*ptr;

	i = 0;
	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		found = 0;
		while (little[found] == big[i + found] && (i + found) < len)
		{
			found++;
			if (found == 1)
				ptr = (char *) &big[i];
			if (found == little_len)
				return (ptr);
		}
		i++;
	}
	return (NULL);
}
