/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:42:59 by migonzal          #+#    #+#             */
/*   Updated: 2023/05/11 12:59:45 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	ft_isspace(char c)
{
	if (c == '\f' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == ' ')
		return (1);
	return (0);
}

static size_t	len_without_extra_spaces(char *str)
{
	size_t		i;
	size_t		len;
	char		found_space;

	len = ft_strlen(str);
	if (str && (len) > 0)
		while ((len - 1) > 0 && str[len - 1] && ft_isspace(str[len - 1]))
			len--;
	str[len] = '\0';
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	len -= i;
	i--;
	found_space = 0;
	while (str[++i])
	{
		if (ft_isspace(str[i]) && !found_space)
			found_space = 1;
		else if (ft_isspace(str[i]))
			len--;
		else
			found_space = 0;
	}
	return (len);
}
*/
int	main()
{
	int fd = open("shell.txt", O_RDWR);
	char *res = get_next_line(fd);

	t_sep *sep = parser(res);
	print_list(sep);
	return (0);
}
