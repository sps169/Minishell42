/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:55:10 by sperez-s          #+#    #+#             */
/*   Updated: 2025/03/26 11:55:45 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cleanse_pipe_list(t_pipe **first)
{
	t_pipe *current;
	t_pipe *next;

	if (!first || !*first)
		return;
	current = *first;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

t_pipe *create_pipe_list(int size)
{
	t_pipe *first;
	t_pipe *prev;
	t_pipe *current;
	int i;

	first = NULL;
	prev = NULL;
	current = NULL;
	i = 0;
	if (size > 0)
	{
		first = malloc(sizeof(t_pipe));
		if (!first)
			return (NULL);
		first->next = NULL;
		current = first;
		while (i < size - 1)
		{
			prev = current;
			current = malloc(sizeof(t_pipe));
			if (!current)
			{
				cleanse_pipe_list(&first);
				return (NULL);
			}
			current->next = NULL;
			prev->next = current;
			prev = current;
			i++;
		}
	}
	return (first);
}
