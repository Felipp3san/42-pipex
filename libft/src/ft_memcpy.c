/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:16:31 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/18 22:39:11 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_c;
	const unsigned char	*src_c;

	if (!dest && !src)
		return (0);
	src_c = (unsigned char *) src;
	dest_c = (unsigned char *) dest;
	while (n--)
		*dest_c++ = *src_c++;
	return (dest);
}
