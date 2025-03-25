#include "minishell.h"


// char *find_path_ret(char *str, t_tools *tools)
// {
// 	int i;

// 	i = 0;
// 	while (tools->envp[i])
// 	{
// 		 if (ft_strncmp(tools->envp[i], str, ft_strlen(str)) == 0)
// 		 {
// 		 	 return ft_substr(tools->envp[i], ft_strlen(str),
//                              ft_strlen(tools->envp[i]) - ft_strlen(str));
// 		 }
// 		 i++;

// 	}
// 	return (NULL);
// }

// int specific_path(t_tools *tools, char *str)
// {
// 	char *aux;
// 	int	ret;
// 	char *str_mod;

// 	aux = find_path_ret(str, tools);
// 	ret = chdir(aux);
// 	free(aux);
// 	if (ret != 0)
// 	{
// 		str_mod = ft_substr(str, 0, ft_strlen(str) - 1);
// 		ft_putstr_fd(str_mod, STDERR_FILENO);
// 		free(str_mod);
// 		ft_putendl_fd(" not set", STDERR_FILENO);
// 	}
// 	return (ret);
// }

// void add_path_to_env(t_tools *tools)
// {
// 	int i;
// 	char *aux;

// 	i = 0;
// 	while(tools->envp[i])
// 	{
// 		if (!ft_strncmp(tools->envp[i], "PWD=", 4))
// 		{
// 			aux = ft_strjoin("PWD=", tools->pwd);
// 			free(tools->envp[i]);
// 			tools->envp[i] = aux;
// 		}
// 		else if (!ft_strncmp(tools->envp[i], "OLDWPD", 7) && tools->old_pwd)
// 		{
// 			aux = ft_strjoin("OLDWPD=", tools->old_pwd);
// 			free(tools->envp[i]);
// 			tools->envp[i] = aux;
// 		}
// 		i++;
		
// 	}
// }

// int cd(t_tools *tools)
// {
// 	int ret;
// 	if (!tools->command->args[1])
// 		ret = specific_path(tools, "HOME=");
// 	else if (ft_strncmp(tools->command->args[1], "-", 1) == 0)
// 		ret =specific_path(tools, "OLDPWD=");
// 	else 
// 	{
// 		ret = chdir(tools->command->args[1]);
// 		if (ret != 0)
// 		{
// 			ft_putstr_fd("minishell: ", STDERR_FILENO);
// 			ft_putstr_fd(tools->command->args[1], STDERR_FILENO);
// 			perror(" ");
// 		}
// 	}
// 	if (ret != 0)
// 		return (EXIT_FAILURE);
// 	change_path(tools);
// 	add_path_to_env(tools);
// 	return (EXIT_SUCCESS);
// }

static void	ft_change_oldpwd_env(t_tools *tools);
static void	ft_change_pwd_env(t_tools *tools);


void	ft_cd(t_command *command, t_tools *tools)
{
	char	*path;

	path = NULL;
	if (command->args[1] && command->args[2])
	{
		printf("cd: too many arguments\n");
		tools->exit_status = 1;
		return;
	}
	ft_change_oldpwd_env(tools);
	if (command->args[1])
		path = ft_strdup(command->args[1]);
	else if (!path)
		path = ft_strdup(getenv("HOME"));
	if (chdir(path))
	{
		perror("cd");
		tools->exit_status = 1;
	}
	else
	{
		tools->exit_status = 0;
	}
	ft_memfree(path);
	ft_change_pwd_env(tools);
}

static void	ft_change_oldpwd_env(t_tools *tools)
{
	char	*to_send;
	char	*path;

	path = getcwd(NULL, 0);
	to_send = ft_strjoin("OLDPWD=", path);
	add_or_update_env(tools, to_send);
	ft_memfree(to_send);
	ft_memfree(path);
}

static void	ft_change_pwd_env(t_tools *tools)
{
	char	*to_send;
	char	*path;

	path = getcwd(NULL, 0);
	to_send = ft_strjoin("PWD=", path);
	add_or_update_env(tools, to_send);
	ft_memfree(to_send);
	ft_memfree(path);
}


