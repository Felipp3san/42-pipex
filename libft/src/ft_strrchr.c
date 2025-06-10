/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:17:39 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/18 22:28:01 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	size_t			str_len;
	size_t			i;

	ch = c;
	str_len = ft_strlen(s);
	i = str_len;
	while (i > 0 && s[i] != ch)
		i--;
	if (s[i] == ch)
		return ((char *) &s[i]);
	return (NULL);
}
