#include "minishell.h"


// int env(t_tools *tools)
// {
//     int i;

//     i = 0;
//     while (tools->envp[i])
//     {
//         ft_putendl_fd(tools->envp[i], STDOUT_FILENO);
//         i++;
//     }
//     return (0);
// }


int ft_env(t_tools *tools)
{
    int i;

    if (tools->command->args[1])
    {
        ft_putstr_fd("env: ", STDERR_FILENO);
        ft_putstr_fd(tools->command->args[1], STDERR_FILENO);
        ft_putendl_fd(": No such file or directory", STDERR_FILENO);
        return (127);
    }
    i = 0;
    while (tools->envp[i])
    {
        ft_putendl_fd(tools->envp[i], STDOUT_FILENO);
        i++;
    }
    return (0);
}

