/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space_in_middle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 08:30:01 by migonzal          #+#    #+#             */
/*   Updated: 2023/02/28 10:21:42 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_space_in_middle(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
	{
		i++;
		if (str[i] && str[i] != ' ')
			return (1);
	}
	return (0);
}
