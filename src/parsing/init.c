#include "minishell.h"


t_command *init_command()
{
	t_command *new_command;

	new_command = (t_command *) malloc(sizeof(t_command));
	if (!new_command)
		return (NULL);
	new_command->cmd_sep = NULL;
	new_command->args = NULL;
	new_command->return_val = 0;
	new_command->next = NULL;
	return (new_command);
}

void free_command(t_command *command)
{
	char **args;
	if (command)
	{
		if (command->cmd_sep)
		{
			args = command->args;
			while (*args)
			{
				free(*args);
				args++;
			}
			free(command->args);
		}
		if (command->redir)
			free(command->redir);
		free(command);
	}
}