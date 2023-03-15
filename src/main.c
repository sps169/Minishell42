/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:05:24 by migonzal          #+#    #+#             */
/*   Updated: 2023/03/15 12:42:26 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_copy	*a = NULL;
	char	*prueba ="ls -lm";

	parsing(prueba, a);
	printf("Hola minishell\n");
	return (0);
}
