/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:35:44 by migonzal          #+#    #+#             */
/*   Updated: 2023/02/28 10:20:31 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*a;
	const char	*b;

	a = (char *) dst;
	b = (const char *) src;
	if (!dst && !src)
		return (0);
	if (dst == src)
		return (dst);
	if (b < a)
	{
		while (len--)
			*(a + len) = *(b + len);
		return (dst);
	}
	while (len--)
		*a++ = *b++;
	return (dst);
}
