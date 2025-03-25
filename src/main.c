/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:42:59 by migonzal          #+#    #+#             */
/*   Updated: 2024/08/05 10:51:32 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int set_built(t_command *command)
// {
// 	static void *arr_built[6][2] = {

	
// 	{"echo", echo},
// 	{"cd", cd},
// 	{"pwd", pwd},
// 	{"export", export},
// 	{"unset", unset},
// 	{"env", env},
// 	};
// 	int i;
// 	i = 0;

// 	while (i < 6)
// 	{
// 		if (command->args[0])
// 		{
// 			if (!ft_strncmp(arr_built[i][0], command->args[0], ft_strlen((arr_built[i][0]))))
// 				return (int)(arr_built[i][1]);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int reset_tools(t_tools *tools)
{
	free_command(tools->command);
	free(tools->arg_str);
	tools->arg_str = NULL;
	ft_free_arr(tools->paths);
	tools->paths = NULL;
	init_tools(tools);
	tools->reset = 1;
	//minishell_loop(tools);
	return (1);


}

int init_tools(t_tools *tools)
{
	tools->arg_str = NULL;
	tools->reset = 0;
	tools->command = init_command();
	parse_envp(tools);
	return (1);

}
int minishell_loop(t_tools *tools)
{
	char *aux;
	int in_dquote = 0;
	int in_squote = 0;

	while(1)
	{
		if (g_signal == S_SIGINT)
			tools->exit_status = 1;
		tools->arg_str = readline("minishell? ");

		
		if (!tools->arg_str)
		{
			ft_putendl_fd("No line read, exit minishell", STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		aux = ft_strtrim(tools->arg_str, " ");
		free(tools->arg_str);
		tools->arg_str = aux;
		if (tools->arg_str[0] == '\0')
		{
			reset_tools(tools);
			continue;
		}
		if (!validate_pipes(tools->arg_str))
		{
			reset_tools(tools);
			continue;
		}

		// Handling unclosed quotes
		for (int i = 0; tools->arg_str[i]; i++)
		{
			if (tools->arg_str[i] == '"' && !in_squote)
				in_dquote = !in_dquote;
			else if (tools->arg_str[i] == '\'' && !in_dquote)
				in_squote = !in_squote;
		}

		while (in_dquote || in_squote)
		{
			char *next_line = readline(in_dquote ? "dquote> " : "quote> ");
			if (!next_line)
			{
				ft_putendl_fd("No line read, exit minishell", STDOUT_FILENO);
				exit(EXIT_SUCCESS);
			}
			aux = ft_strjoin(tools->arg_str, "\n");
			free(tools->arg_str);
			tools->arg_str = ft_strjoin(aux, next_line);
			free(aux);
			free(next_line);

			in_dquote = 0;
			in_squote = 0;
			for (int i = 0; tools->arg_str[i]; i++)
			{
				if (tools->arg_str[i] == '"' && !in_squote)
					in_dquote = !in_dquote;
				else if (tools->arg_str[i] == '\'' && !in_dquote)
					in_squote = !in_squote;
			}
		}

		add_history(tools->arg_str);
		expansor(tools);
		tools->command = parser(tools->arg_str);
		executor(tools);
		reset_tools(tools);
	}
	return (1);
}


// int minishell_loop(t_tools *tools)
// {
// 	char *aux;

// 	while(1)
// 	{
// 		//printf("Waiting for command...\n");
// 		tools->arg_str = readline("minishell? ");
// 		if (!tools->arg_str)
// 		{
// 			ft_putendl_fd("No line read, exit minishell", STDOUT_FILENO);
// 			exit(EXIT_SUCCESS);
// 		}
// 		//printf("Command read: %s\n", tools->arg_str);
// 		aux = ft_strtrim(tools->arg_str, " ");
// 		if (aux == NULL)
//         {
//             free(tools->arg_str);
//             continue;
//         }
// 		free(tools->arg_str);
// 		tools->arg_str = aux;
// 		if (tools->arg_str[0] == '\0')
// 		{
// 			reset_tools(tools);
// 			continue;
// 		}
// 		add_history(tools->arg_str);
// 		// if (!count_quotes(tools->arg_str))
// 		//	return (ft_error()); // HACER FUNCION
// 		expansor(tools);
// 		tools->command = parser(tools->arg_str);
// 		//env(tools);
// 		executor(tools);
// 		//print_list(tools->command);
// 		reset_tools(tools);
// 		}
// 	return (1);

// }

int	main(int argc, char **argv, char **envp)
{
	t_tools tools;

	if (argc != 1 || argv[1])
	{
		printf("Este programa no acepta argumentos inútil\n");
		exit(0);
	}
	tools.envp = arrdup(envp);
	signal_init();
	find_pwd(&tools);
	init_tools(&tools);
	printf("AQUI EMPIEZA LA MINISHELL\n");
	minishell_loop(&tools);
	return (0);
}
//char *expansor(t_tools *tools, char *str)
