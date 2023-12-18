#include "minishell.h"


int	variable_exist(t_tools *tools, char *str)
{
	int i;

	i = 0;
	if (str[equal_after(str)] == '\"')
		delete_quotes(str, '\"');
	if (str[equal_after(str)] == '\'')
		delete_quotes(str, '\'');
	while (tools->envp[i])
	{
		if (ft_strncmp(tools->envp[i],
		 str, equal_after(tools->envp[i])) == 0)
		 {
			free(tools->envp[i]);
			tools->envp[i] = ft_strdup(str);
			return (i);
		 }
		 i++;
	}
	return (0);
}

int export_error(char *str)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (str)
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\': is ", STDERR_FILENO);
	}
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int check_parameter(char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (export_error(str)); 
	if (equal_after(str) == 0)
		return (EXIT_FAILURE);
	if (str[0] == '=')
		return (export_error(str)); 
	while (str[i] != '=')
	{
		if (check_valid_identifier(str[i]))
			return (export_error(str)); 
		i++;
	}
	return (EXIT_SUCCESS);
}


char **loop_add_var(char **arr, char **aux, char *str)
{
	int i;

	i = 0;
	while(arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
		{
			aux[i] = ft_strdup(str);
			aux[i +1] = ft_strdup(arr[i]);
		}
		else
			aux[i] =ft_strdup(arr[i]);
		if (aux[i] == NULL)
		{
			ft_free_arr(aux);
			return (aux);
		}
		i++;
	}
	return (aux);
}

char **add_var(char **arr, char *str)
{
	char **aux;
	size_t i;

	i = 0;
	if (str[equal_after(str)] == '\'')
		delete_quotes(str, '\'');
	if (str[equal_after(str)] == '\"')
		delete_quotes(str, '\"');
	while (arr[i] != NULL)
		i++;
	aux =ft_calloc(sizeof(char *), i +2);
	if (!aux)
		return (NULL);
	i = 0;
	loop_add_var(arr, aux, str);
	return (aux);
}


int export(t_tools *tools, t_sep *sep)
{
	char **aux;
	int i;

	i = 1;
	if (!sep->args[1] || sep->args[1][0] == '\0')
		env(tools, sep);
	else
	{
		while (sep->args[i])
		{
			if (check_parameter(sep->args[i]) == 0
				&& variable_exist(tools, sep->args[i]) == 0)
			{
				if (sep->args[i])
				{
					aux = add_var(tools->envp, sep->args[i]);
					ft_free_arr(tools->envp);
					tools->envp = aux;
				}
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
