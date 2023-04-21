/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:12:02 by sperez-s          #+#    #+#             */
/*   Updated: 2023/04/21 13:28:05 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(int argc, char *argv[], int nl, int fd)
{
	int	err;
	int	i;

	err = 0;
	i = 0;
	if (argc > 1)
	{
		while (argv[i])
		{
			if (write(fd, argv[i], ft_strlen(argv[i])) == -1)
				err++;
			i++;
		}
	}
	if (nl && write(1, "\n", 1))
		err++;
	return (err);
}
