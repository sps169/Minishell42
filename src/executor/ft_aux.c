

# include "minishell.h"

int is_builtin(t_tools *tools)
{
	return (built_comprobation(tools));
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

int get_command_list_size(t_command *list)
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

void fd_redir(t_redir *redir) {

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







