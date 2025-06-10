/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbdigits_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:32:32 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/25 21:32:34 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbdigits_base(unsigned long long nbr, size_t base_len)
{
	size_t	count;

	count = 1;
	while (nbr >= base_len)
	{
		nbr = nbr / base_len;
		count++;
	}
	return (count);
}
