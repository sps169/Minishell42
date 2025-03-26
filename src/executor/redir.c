/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:04:01 by sperez-s          #+#    #+#             */
/*   Updated: 2025/03/26 12:12:43 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int handle_heredoc(t_redir *redir) {
    char *line;
    int pipe_fd[2];

    // Crear una tubería para capturar la entrada
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return -1;
    }

    // Prompt para que el usuario introduzca líneas hasta que se encuentra el delimitador
    while (1) {
        line = readline("> ");
        if (line == NULL) {
            // Fin de la entrada (Ctrl+D)
            break;
        }

        // Comprobar si la línea coincide con el delimitador
        if (strcmp(line, redir->file) == 0) {
            free(line);
            break;
        }

        // Escribir la línea en la tubería
        write(pipe_fd[1], line, strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);

    // Redirigir el extremo de lectura de la tubería a stdin
    redir->fd = pipe_fd[0];
    return 1;
}

static int file_open(t_redir *redir) {
	
	int	mode;
 
	if ((redir-> type == 3 && redir-> fd != 0) || access(redir->file, F_OK) != -1)
	{
		//printf("DEBUG: %s exists\n", redir->file);
		if (redir->type == 0 || redir->type == 2)
			mode = R_OK;
		else
			mode = R_OK | W_OK;
		if (access(redir->file, mode) != -1)
		{
			if (redir->type == 3)
				mode = O_RDWR | O_APPEND;
			redir->fd = open(redir->file, mode);
		}
		return (1);
	}
	else if (redir->type == 1 || redir->type == 3) {
		mode = O_CREAT | O_RDWR;
		if (redir->type == 3)
			mode = mode | O_APPEND;
		redir->fd = open(redir->file, mode, S_IRGRP | S_IWUSR | S_IRUSR | S_IROTH);
		//printf("DEBUG: %s: file open at fd %i\n", redir->file, redir->fd);
	} else if  (redir->type == 2) {
		return (handle_heredoc(redir));
	
	} else {
		printf("Minishell: %s: File or directory does not exist\n", redir->file);
		return (0);
	}
	return (1);
}

static void fd_redir(t_redir *redir) {

	if (redir->type == 0 || redir->type == 2)
		dup2(redir->fd, STDIN_FILENO);
	else 
		dup2(redir->fd, STDOUT_FILENO);
	close(redir->fd);
	//printf("DEBUG: redir of type %i applied to fd %i\n", redir->type, redir->fd);
}

int redir_setup(t_command *command) {
	
	t_redir *curr_redir;
	t_redir	*first_redir;
	
	curr_redir = command->redir;
	first_redir = command->redir;
	while (curr_redir)
	{
		if (file_open(curr_redir) != 1)
			return -1;
		curr_redir = curr_redir->next;
	}
	curr_redir = first_redir;
	while(curr_redir) 
	{
		fd_redir(curr_redir);
		curr_redir = curr_redir->next;
	}
	return (0);
}