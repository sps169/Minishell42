#include "minishell.h"

static void	ft_eraser(char *name, t_env *ptr);
static void	del_variable(t_env *node);


void	ft_unset(t_tools *tools)
{
	t_env	*ptr;
	int		i;

	i = 0;
	if (!tools->command->args[i])
		return ;
	tools->exit_status = 0;
	while (tools->command->args[++i])
	{
		ptr = tools->env;
		if (!ptr)
			return ;
		ft_eraser(tools->command->args[i], ptr);
	}
}


static void	ft_eraser(char *name, t_env *ptr)
{
	if (!ft_strcmp(name, ptr->next->var_name))
		return ;
	while (ptr && ptr->next)
	{
		if (!ft_strcmp(name, ptr->next->var_name))
		{
			del_variable(ptr->next);
			ptr->next = ptr->next->next;
			return ;
		}
		ptr = ptr->next;
	}
}

static void	del_variable(t_env *node)
{
	ft_memfree(node->var_name);
	ft_memfree(node->value_var);
	ft_memfree(node);
}