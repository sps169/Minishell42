#include "minishell.h"

// static void	ft_eraser(char *name, t_env *ptr);
// static void	del_variable(t_env *node);


// void	ft_unset(t_tools *tools)
// {
// 	t_env	*ptr;
// 	int		i;

// 	i = 0;
// 	if (!tools->command->args[i])
// 		return ;
// 	tools->exit_status = 0;
// 	while (tools->command->args[++i])
// 	{
// 		ptr = tools->env;
// 		if (!ptr)
// 			return ;
// 		ft_eraser(tools->command->args[i], ptr);
// 	}
// }


// static void	ft_eraser(char *name, t_env *ptr)
// {
// 	if (!ft_strcmp(name, ptr->next->var_name))
// 		return ;
// 	while (ptr && ptr->next)
// 	{
// 		if (!ft_strcmp(name, ptr->next->var_name))
// 		{
// 			del_variable(ptr->next);
// 			ptr->next = ptr->next->next;
// 			return ;
// 		}
// 		ptr = ptr->next;
// 	}
// }

// static void	del_variable(t_env *node)
// {
// 	ft_memfree(node->var_name);
// 	ft_memfree(node->value_var);
// 	ft_memfree(node);
// }


static void	unset_variable(t_tools *tools, char *name)
{
	int i = 0;
	int j = 0;
	int len = ft_strlen(name);
	char **new_envp;

	// Contar el número de variables de entorno
	while (tools->envp[i])
		i++;

	// Crear una nueva lista de variables de entorno
	new_envp = malloc(sizeof(char *) * i);
	if (!new_envp)
		return;

	i = 0;
	while (tools->envp[i])
	{
		// Copiar todas las variables excepto la que se va a eliminar
		if (!(ft_strncmp(tools->envp[i], name, len) == 0 && tools->envp[i][len] == '='))
		{
			new_envp[j] = tools->envp[i];
			j++;
		}
		else
		{
			free(tools->envp[i]);
		}
		i++;
	}

	// Terminar la nueva lista con NULL
	new_envp[j] = NULL;

	// Reemplazar la vieja lista de variables de entorno con la nueva
	free(tools->envp);
	tools->envp = new_envp;
}

void	ft_unset(t_tools *tools)
{
	int i = 1; // Iniciar en 1 para omitir el nombre del comando

	if (!tools->command->args[i])
		return;

	tools->exit_status = 0;

	while (tools->command->args[i])
	{
		unset_variable(tools, tools->command->args[i]);
		i++;
	}
}