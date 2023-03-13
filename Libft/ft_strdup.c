/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:37:36 by migonzal          #+#    #+#             */
/*   Updated: 2022/12/02 12:20:14 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*aux;
	size_t	len;

	len = ft_strlen(s1) + 1;
	aux = malloc (sizeof(char) * len);
	if (!aux)
		return (0);
	aux = ft_memcpy(aux, s1, len);
	return (aux);
}
