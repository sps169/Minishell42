#include "minishell.h"


char *find_path_ret(char *str, t_tools *tools)
{
	int i;

	i = 0;
	while (tools->envp[i])
	{
		 if (ft_strncmp(tools->envp[i], str, ft_strlen(str)) == 0)
		 {
		 	 return ft_substr(tools->envp[i], ft_strlen(str),
                             ft_strlen(tools->envp[i]) - ft_strlen(str));
		 }
		 i++;

	}
	return (NULL);
}

int specific_path(t_tools *tools, char *str)
{
	char *aux;
	int	ret;
	char *str_mod;

	aux = find_path_ret(str, tools);
	ret = chdir(aux);
	free(aux);
	if (ret != 0)
	{
		str_mod = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str_mod, STDERR_FILENO);
		free(str_mod);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

void add_path_to_env(t_tools *tools)
{
	int i;
	char *aux;

	i = 0;
	while(tools->envp[i])
	{
		if (!ft_strncmp(tools->envp[i], "PWD=", 4))
		{
			aux = ft_strjoin("PWD=", tools->pwd);
			free(tools->envp[i]);
			tools->envp[i] = aux;
		}
		else if (!ft_strncmp(tools->envp[i], "OLDWPD", 7) && tools->old_pwd)
		{
			aux = ft_strjoin("OLDWPD=", tools->old_pwd);
			free(tools->envp[i]);
			tools->envp[i] = aux;
		}
		i++;
		
	}
}

int cd(t_tools *tools, t_command *command)
{
	int ret;
	if (!command->args[1])
		ret = specific_path(tools, "HOME=");
	else if (ft_strncmp(command->args[1], "-", 1) == 0)
		ret =specific_path(tools, "OLDPWD=");
	else 
	{
		ret = chdir(command->args[1]);
		if (ret != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(command->args[1], STDERR_FILENO);
			perror(" ");
		}
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	change_path(tools);
	add_path_to_env(tools);
	return (EXIT_SUCCESS);
}

