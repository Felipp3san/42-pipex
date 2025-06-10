/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:56:00 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/25 13:15:21 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_printnbr(int nbr, int padding, int fd);
size_t	ft_printstr(char *str, int fd);
size_t	ft_printchar(char ch, int fd);
size_t	ft_printptr(uintptr_t ptr, int fd);
size_t	ft_printunbr_base(unsigned int nbr, const char *base, int fd);

/*
 * %c - char
 * %s - string
 * %p - pointer (printed in hex)
 * %d - decimal (base 10)
 * %i - integer (base 10)
 * %u - unsigned decimal (base 10)
 * %x - number in hex (base 16 - lowercase)
 * %X - number in hex (base 16 - uppercase)
 * %% - percent sign
*/

static int	printf_format(int fd, va_list *va, char ch, int padding)
{
	const char	*base10 = "0123456789";
	const char	*base16 = "0123456789abcdef";
	const char	*base16u = "0123456789ABCDEF";

	if (ch == 'c')
		return (ft_printchar((char)va_arg(*va, int), fd));
	else if (ch == 'd' || ch == 'i')
		return (ft_printnbr(va_arg(*va, int), padding, fd));
	else if (ch == 'u')
		return (ft_printunbr_base(va_arg(*va, unsigned int), base10, fd));
	else if (ch == 'p')
		return (ft_printptr((uintptr_t) va_arg(*va, void *), fd));
	else if (ch == 's')
		return (ft_printstr(va_arg(*va, char *), fd));
	else if (ch == 'x')
		return (ft_printunbr_base(va_arg(*va, unsigned int), base16, fd));
	else if (ch == 'X')
		return (ft_printunbr_base(va_arg(*va, unsigned int), base16u, fd));
	else
		return (ft_printchar(ch, fd));
}

static int	get_digits(char **fstring)
{
	char	*width;
	int		size;
	int		i;

	size = 0;
	while (ft_isdigit((*fstring)[size]) || (*fstring)[size] == '-')
		size++;
	width = (char *) malloc(size + 1);
	if (!width)
		return (0);
	i = 0;
	while (i < size)
	{
		width[i] = **fstring;
		(*fstring)++;
		i++;
	}
	width[i] = '\0';
	return (ft_atoi(width));
}

int	ft_printf(const char *fstring, ...)
{
	va_list	va;
	size_t	ch_count;
	int		padding;

	ch_count = 0;
	va_start(va, fstring);
	while (*fstring)
	{
		if (*fstring == '%')
		{
			padding = 0;
			if (ft_isdigit(*(++fstring)) || *fstring == '-')
				padding = get_digits((char **)&fstring);
			ch_count += printf_format(1, &va, *fstring, padding);
		}
		else
		{
			ft_putchar_fd(*fstring, 1);
			ch_count++;
		}
		fstring++;
	}
	va_end(va);
	return (ch_count);
}
