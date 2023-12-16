#include "minishell.h"


int pwd(t_tools *tools)
{
    ft_putend_fd(tools->pwd, STDOUT_FILENO);
    return (0);
}