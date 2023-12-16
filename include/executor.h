/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:25:03 by sperez-s          #+#    #+#             */
/*   Updated: 2023/11/21 21:59:06 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <errno.h>
# include <unistd.h>
typedef struct s_command
{
	const char			*command;
	struct s_command	*next;
	char *input;
	char *output;
	int	heredoc;
	int	append;
}	t_command;

typedef struct s_pipe
{
	int				pipe[2];
	struct	s_pipe	*next;
}	t_pipe;
#endif
