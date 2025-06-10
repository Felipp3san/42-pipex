/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:24:49 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/25 21:18:59 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa_base(unsigned int nbr, const char *base)
{
	char	*str;
	size_t	nbdigits;
	size_t	base_size;

	base_size = ft_strlen(base);
	if (base_size < 2)
		return (NULL);
	nbdigits = ft_nbdigits_base(nbr, base_size);
	str = (char *) malloc(nbdigits + 1);
	if (!str)
		return (str);
	str[nbdigits] = '\0';
	while (nbdigits >= 1)
	{
		str[--nbdigits] = base[nbr % base_size];
		nbr = nbr / base_size;
	}
	return (str);
}
