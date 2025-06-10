/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:20:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/25 19:21:06 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	apply_padding(int fd)
{
	ft_putchar_fd(' ', fd);
	return (1);
}

size_t	ft_printnbr(int nbr, int padding, int fd)
{
	char	*str;
	size_t	size;

	str = ft_itoa(nbr);
	size = ft_strlen(str);
	if (padding > 0)
	{
		while (size < (unsigned long) padding)
			size += apply_padding(fd);
	}
	ft_putstr_fd(str, fd);
	if (padding < 0)
	{
		padding = -padding;
		while (size < (unsigned long) padding)
			size += apply_padding(fd);
	}
	free(str);
	return (size);
}
