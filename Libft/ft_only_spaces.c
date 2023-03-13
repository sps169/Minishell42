/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_only_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:49:05 by migonzal          #+#    #+#             */
/*   Updated: 2022/12/02 11:33:49 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (i == (int)ft_strlen(str))
		return (1);
	return (0);
}
