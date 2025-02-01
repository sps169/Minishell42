#include "minishell.h"

char **loop_delete_var(char **arr, char **aux, char *str)
{
  int i;
  int j;

  i = 0;
  j = 0;

  while (arr[i] != NULL)
  {
    if (!(ft_strncmp(arr[i], str, equal_after(arr[i]) -1) == 0
		&& str[equal_after(arr[i])] == '\0'
		&& arr[i][ft_strlen(str)] == '='))
	{
		aux[j] = ft_strdup(arr[i]);
		if (aux[i] == NULL)
		{
			ft_free_arr(aux);
			return (aux);
		}
		j++;
	}
	i++;
  }
  return (aux);
}

char **delete_var(char **arr, char *str)
{
	char **aux;
	size_t i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	aux = ft_calloc(sizeof(char *), i +1);
	if (!aux)
		return (NULL);
	aux = loop_delete_var(arr, aux, str);
	return (aux);
}


int unset_error(t_tools *tools)
{
	int i;

	i = 0;
	if (tools->command->args[1])
	{
		ft_putendl_fd("minishell: unset not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (tools->command->args[1][i])
	{
		if (tools->command->args[1][i++] == '/')
		{
			ft_putstr_fd("minishell: unset '", STDERR_FILENO);
			ft_putstr_fd(tools->command->args[1], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		}
	}
	if (equal_after(tools->command->args[1]) != 0)
	{
		ft_putendl_fd("minishell: unset: not a valid identifier", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}


int unset(t_tools *tools)
{
	char **aux;

	if (unset_error(tools) == 1)
		return (EXIT_FAILURE);
	else
	{
		aux =delete_var(tools->envp, tools->command->args[1]);
		ft_free_arr(tools->envp);
		tools->envp = aux;
	}
	return (EXIT_SUCCESS);
}
