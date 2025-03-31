/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:04:58 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/18 20:13:11 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *parser(char *s)
{
	char **aux = split_minishell(s, '|');
	t_command *sep = NULL;
	int i = 0;

	while (aux[i])
	{
		sep = add_cell(sep, aux[i]);
		i++;
	}
	return (sep);
}
