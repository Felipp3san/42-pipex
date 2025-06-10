/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:25:41 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/18 21:28:19 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*src_c;
	unsigned char		*dest_c;

	if (!dest && !src)
		return (0);
	src_c = (const unsigned char *) src;
	dest_c = (unsigned char *) dest;
	if (dest_c <= src_c)
	{
		while (n--)
			*dest_c++ = *src_c++;
	}
	else
	{
		dest_c += n - 1;
		src_c += n - 1;
		while (n--)
			*dest_c-- = *src_c--;
	}
	return (dest);
}
