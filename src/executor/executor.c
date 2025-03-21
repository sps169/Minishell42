/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:25:07 by sperez-s          #+#    #+#             */
/*   Updated: 2025/03/22 15:19:30 by migonzal         ###   ########.fr       */
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

int	fill_command_from_env(t_command *command, t_tools *tools)
{
	int		found;
	int		i;
	char	*joined;

	found = 0;
	i = 0;
	while (tools->paths[i] && !found)
	{
		joined = ft_strjoin(tools->paths[i], command->args[0]);
		if (access(joined, R_OK | X_OK) != -1)
		{
			free(command->args[0]);
			command->args[0] = joined;
			found = 1;
		}
		else 
			free(joined);
		i++;
	}
	if (found == 0)
	{
		printf("%s: command not found\n", command->args[0]);
		return (-1);
	}
	errno = 0;
	return (0);
}

static int get_command_list_size(t_command *list)
{
	int i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
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

static int redir_setup(t_command *command) {
	
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


static int is_builtin(t_tools *tools)
{
	return (built_comprobation(tools));
}
static void run_command(t_command *command, t_tools *tools) 
{
	int aux = is_builtin(tools);
	printf("Valor de aux: %d\n", aux);

	if (redir_setup(command) == 0)
	{
		if (is_builtin(tools))
		{
			write(1, "HOLA\n", 5);
			ft_builtin(tools);
		}
		else
		{
			write(1, "HOLO\n", 5);
			execve(command->args[0], command->args, tools->envp);
		}
	}
}

static int exec_single_command(t_command *command, t_tools *tools) {
	
	int	pid;
	int	status;
	printf("Valor de arg[0]: %s\n", tools->command->args[0]);

	if (fill_command_from_env(command, tools) == -1)
		return -1;
	if (is_builtin(tools))
	{
		write(1, "HOLI\n", 5);
		ft_builtin(tools);
		return (0);
	}
	//printf("DEBUG: filled command %s\n", command->args[0]);
	pid = fork();
	if (pid == 0)
	{
		run_command(command, tools);
		return (-1);
	}
	else if(pid > 0) {
		//printf("DEBUG: Parent starts waiting\n");
		waitpid(pid, &status, 0);
		//printf("DEBUG: Parent finish wait, child status -> %i\n", status);
	} else {
		printf("ERROR: fork failed with errno: %d\n", errno);	
		return -1;
	}
	return status;
	
 }

int executor(t_tools *tools)
{
	unsigned int size;
	t_pipe *ps;
	unsigned int i;
	int child_status;
	int pid;
	t_pipe *prev_pipe;
	t_command *curr_command;


	i = 0;
	prev_pipe = NULL;
	size = get_command_list_size(tools->command);
	if (size < 1)
	{
		printf("ERROR: empty command list\n");
		return (0);
	}
	if (size == 1)
	{
		//printf("DEBUG: single command exec\n");
		return (exec_single_command(tools->command, tools));
	}
	//printf("DEBUG: multi command exec\n");
	ps = create_pipe_list(size);
	if (!ps)
	{
		write(2, "ERROR: Could't create pipe list\n", 33);
		return (-1);
	}
	curr_command = tools->command;
	while (i < size)
	{
		if (fill_command_from_env(curr_command, tools) != -1) {

			if (i != size - 1) //dont make new pipe at last command
				pipe(ps->pipe);
			pid = fork();
			if (pid == 0)
			{
				if (i != size - 1)//not last
				{
					dup2(ps->pipe[1], STDOUT_FILENO);
					close(ps->pipe[0]);
					close(ps->pipe[1]);
				}
				if (i != 0)//not first
				{
					dup2(prev_pipe->pipe[0], STDIN_FILENO);
					close(prev_pipe->pipe[0]);
				}
				run_command(curr_command, tools);
				return (-1);
			}
			else
			{
				if (i != size - 1) //not last
				{
					close(ps->pipe[1]);
				}
				if (prev_pipe)
					close(prev_pipe->pipe[0]);
				waitpid(pid, &child_status, 0);
			}
		}
		if (curr_command)
		{
			curr_command = curr_command->next;
		}
		if (ps)
		{
			prev_pipe = ps;
			ps = ps->next;
		}
		i++;
	}
	return (0);
}
