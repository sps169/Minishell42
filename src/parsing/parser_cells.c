/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cells.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 10:25:18 by migonzal          #+#    #+#             */
/*   Updated: 2025/03/25 19:00:48 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"



static int	skip_spaces_and_validate(char *redir, int *i)
{
	while (redir[*i] && (redir[*i] == ' '
			|| redir[*i] == '\t' || redir[*i] == '\n'))
		*i = *i + 1;
	if (redir[*i] && (redir[*i] == '\\'
			|| redir[*i] == '<' || redir[*i] == '>'))
		return (-1);
	return (0);
}

static char	*allocate_file(char *word_start, size_t length, int *status)
{
	char	*file;

	file = ft_calloc(1, sizeof(char) * (length + 1));
	if (!file)
	{
		*status = -1;
		return (NULL);
	}
	if (ft_strlcpy(file, word_start, length + 1) < length)
	{
		free(file);
		*status = -1;
		return (NULL);
	}
	return (file);
}

static void	update_length_and_index(size_t *length, int *i)
{
	*length += 1;
	*i += 1;
}

char	*locate_redir_file(char *redir, int *i, int *status)
{
	char	quote;
	char	*word_start;
	size_t	length;

	quote = 0;
	word_start = NULL;
	length = 0;
	if (skip_spaces_and_validate(redir, i) == -1)
	{
		*status = -1;
		return (NULL);
	}
	word_start = redir + *i;
	while (redir[*i] && word_start)
	{
		if (quote == 0 && (redir[*i] == '"' || redir[*i] == '\''))
			quote = redir[*i];
		else if (quote && redir[*i] == quote)
			quote = 0;
		else if (quote == 0 && (redir[*i] == ' ' || redir[*i] == '\t'
				|| redir[*i] == '\n' || redir[*i] == '<' || redir[*i] == '>'))
			break ;
		update_length_and_index(&length, i);
	}
	if (length == 0)
	{
		*status = -1;
		return (NULL);
	}
	return (allocate_file(word_start, length, status));
}
