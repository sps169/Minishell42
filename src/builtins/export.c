#include "minishell.h"


// static void		ft_export_without_arg(t_tools *tools);
// static t_env	*sort_list(t_env *lst);
// static t_env	*copy_list(t_env *lst);
// static int		check_export(char *arg);

// void	ft_export(t_tools *tools)
// {
// 	int	i;

// 	tools->exit_status = 0;
// 	if (tools->command->args[1] == NULL)
// 		ft_export_without_arg(tools);
// 	else
// 	{
// 		i = 0;
// 		while (tools->command->args[++i])
// 		{
// 			if (check_export(tools->command->args[i]))
// 				add_arg_to_env(tools->command->args[i], tools);
// 			else
// 				tools->exit_status = 1;
// 		}
// 	}
// }

// static void	ft_export_without_arg(t_tools *tools)
// {
// 	t_env	*tmp;
// 	t_env	*lst_cpy;

// 	lst_cpy = copy_list(tools->env);
// 	tmp = sort_list(lst_cpy);
// 	while (tmp)
// 	{
// 		if (!ft_strncmp(tmp->var_name, "_\0", 2))
// 			printf(" \r");
// 		else if (tmp->value_var[0])
// 			printf("declare -x %s=\"%s\"\n", tmp->var_name, tmp->value_var);
// 		else
// 			printf("declare -x %s\n", tmp->var_name);
// 		tmp = tmp->next;
// 	}
// 	ft_free_list(&lst_cpy);
// }

// static t_env	*sort_list(t_env *lst)
// {
// 	t_env	*tmp;
// 	t_env	*swap;

// 	tmp = lst;
// 	swap = ft_lstnew_env("", "", 0);
// 	while (lst->next != NULL)
// 	{
// 		if (lst->next && ft_strcmp(lst->var_name, lst->next->var_name) > 0)
// 		{
// 			swap->var_name = lst->var_name;
// 			swap->value_var = lst->value_var;
// 			lst->var_name = lst->next->var_name;
// 			lst->value_var = lst->next->value_var;
// 			lst->next->var_name = swap->var_name;
// 			lst->next->value_var = swap->value_var;
// 			lst = tmp;
// 		}
// 		else
// 			lst = lst->next;
// 	}
// 	lst = tmp;
// 	ft_memfree(swap);
// 	return (lst);
// }

// static t_env	*copy_list(t_env *lst)
// {
// 	t_env	*cpy;
// 	t_env	*tmp;

// 	tmp = lst;
// 	cpy = NULL;
// 	while (tmp)
// 	{
// 		if (!cpy)
// 			cpy = ft_lstnew_env(tmp->var_name, tmp->value_var, 1);
// 		else
// 			ft_lstadd_back_env(&cpy, ft_lstnew_env(tmp->var_name,
// 						tmp->value_var, 1));
// 		tmp = tmp->next;
// 	}
// 	return (cpy);
// }

// static int	check_export(char *arg)
// {
// 	int		i;
// 	char	*name;

// 	i = 0;
// 	name = get_env_name(arg);
// 	if (ft_isdigit(name[i]))
// 	{
// 		printf("export: %s: not a valid identifier\n", arg); //OJO
// 		return (ft_memfree(name), 0);
// 	}
// 	while (name[i])
// 	{
// 		if (ft_isalnum(name[i]) || name[i] == '_')
// 			i++;
// 		else
// 		{
// 			printf("export: %s: not a valid identifier\n", arg); //OJO
// 			return (ft_memfree(name), 0);
// 		}
// 	}
// 	return (ft_memfree(name), 1);
// }


static void	print_env(t_tools *tools)
{
	int i = 0;

	while (tools->envp[i])
	{
		printf("%s\n", tools->envp[i]);
		i++;
	}
}


static void	add_or_update_env(t_tools *tools, char *var)
{
	char *name = get_env_name(var);
	char *value = get_env_value(var);
	int i = 0;

	while (tools->envp[i])
	{
		if (ft_strncmp(tools->envp[i], name, ft_strlen(name)) == 0 && tools->envp[i][ft_strlen(name)] == '=')
		{
			free(tools->envp[i]);
			tools->envp[i] = ft_strjoin(name, "=");
			tools->envp[i] = ft_strjoin(tools->envp[i], value);
			free(name);
			free(value);
			return;
		}
		i++;
	}

	tools->envp = realloc(tools->envp, (i + 2) * sizeof(char *));
	tools->envp[i] = ft_strjoin(name, "=");
	tools->envp[i] = ft_strjoin(tools->envp[i], value);
	tools->envp[i + 1] = NULL;
	free(name);
	free(value);
}

void	ft_export(t_tools *tools)
{
	int	i;

	tools->exit_status = 0;

	if (tools->command->args[1] == NULL)
	{
		print_env(tools);
	}
	else
	{
		i = 1; // Iniciar en 1 para omitir el nombre del comando
		while (tools->command->args[i])
		{
			add_or_update_env(tools, tools->command->args[i]);
			i++;
		}
	}
}
