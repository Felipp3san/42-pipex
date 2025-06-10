/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:31:46 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/18 22:34:44 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(unsigned int n)
{
	size_t	size;

	if (n == 0)
		return (1);
	size = 0;
	while (n > 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	size_t			size;
	char			*str;
	int				is_neg;
	int				i;

	is_neg = n < 0;
	if (is_neg)
		nbr = (unsigned int)-n;
	else
		nbr = (unsigned int)n;
	size = get_size(nbr);
	str = (char *) malloc(size + is_neg + 1);
	if (!str)
		return (str);
	i = size + is_neg;
	str[i--] = '\0';
	while (i >= 0 + is_neg)
	{
		str[i--] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	if (is_neg)
		str[0] = '-';
	return (str);
}
