/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:57:01 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/18 21:43:14 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len;

	len = ft_strlen(s1);
	len += ft_strlen(s2);
	dst = (char *) malloc(len + 1);
	if (dst)
	{
		*dst = '\0';
		ft_strlcat(dst, s1, len + 1);
		ft_strlcat(dst, s2, len + 1);
	}
	return (dst);
}
