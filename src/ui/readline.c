/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:33:51 by sperez-s          #+#    #+#             */
/*   Updated: 2023/05/11 13:54:11 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

//gccw -lreadline readline.c

int main(void)
{
	char	*buf;
	int		i;
	
	buf = NULL;
	i = 0;
	buf = readline(">_");
	while (buf != NULL)
	{
		if (i != 0)
			buf = readline(">_");
		if (strlen(buf) > 0) {
			add_history(buf);
		}
		printf("[%s]\n", buf);
		free(buf);
		i++;
	}

	return (0);
}
