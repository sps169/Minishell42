/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:04:58 by migonzal          #+#    #+#             */
/*   Updated: 2023/05/09 10:18:41 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sep *parser(char *s)
{
	char **aux = split_minishell(s, '|');
	t_sep *sep;
	int i = 0;

	while (aux[i])
	{
		//printf("String: %s\n", aux[i]);
		sep = add_cell(sep, aux[i], i);
		i++;
	}
	return (sep);
}
