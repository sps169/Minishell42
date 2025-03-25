
#include "minishell.h"


void handle_status(int status, t_tools *tools)
{
	if (WIFEXITED(status))
		tools->exit_status = WEXITSTATUS(status);
	if (tools && tools->exit_status == 127)
		printf("%s: command not found\n", tools->command->args[0]);
	if (g_signal == S_SIGINT_CMD)
		tools->exit_status = 130;
	g_signal = S_BASE;
}

void run_command(t_command *command, t_tools *tools) 
{
	if (redir_setup(command) == 0)
	{
		if (is_builtin(tools) == 1)
			ft_builtin(tools);
		else
			execve(command->args[0], command->args, tools->envp);
	}
}

