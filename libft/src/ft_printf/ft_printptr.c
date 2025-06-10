/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:37:15 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/25 19:40:13 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_printstr(char *str, int fd);

static int	ptr_hex(uintptr_t ptr, int fd, int size)
{
	const char		*base = "0123456789abcdef";
	const size_t	base_size = 16;

	if (ptr >= base_size)
		size = ptr_hex(ptr / base_size, fd, size);
	ft_putnbr_base_fd((int)(ptr % base_size), (char *)base, fd);
	return (size + 1);
}

size_t	ft_printptr(uintptr_t ptr, int fd)
{
	size_t	size;

	if (!ptr)
		return (ft_printstr("(nil)", fd));
	ft_putstr_fd("0x", fd);
	size = ptr_hex(ptr, fd, 2);
	return (size);
}
