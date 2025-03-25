
#include "minishell.h"


static t_pipe *initialize_pipe_nodes(int size, t_pipe *first) {
    t_pipe *prev;
    t_pipe *current;
    int i;

    prev = NULL;
    current = first;
    i = 0;
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
    return first;
}

static int find_command_path(t_command *command, t_tools *tools) {
    int found;
    int i;
    char *joined;

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
    return found;
}

t_pipe *create_pipe_list(int size)
{
    t_pipe *first;

    first = NULL;
    if (size > 0)
    {
        first = malloc(sizeof(t_pipe));
        if (!first)
            return (NULL);
        first->next = NULL;
        first = initialize_pipe_nodes(size, first);
        if (!first)
            return (NULL);
    }
    return (first);
}



int	fill_command_from_env(t_command *command, t_tools *tools)
{
    int found;

    if (is_builtin(tools))
        return (0);

    found = find_command_path(command, tools);

    if (found == 0)
    {
        printf("%s: command not found\n", command->args[0]);
        return (-1);
    }
    errno = 0;
    return (0);
}