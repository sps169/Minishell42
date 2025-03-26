# include "minishell.h"


char *ft_strstr(const char *haystack, const char *needle) {
    size_t i;
    size_t j;

    if (needle[0] == '\0')
        return (char *)haystack;

    for (i = 0; haystack[i] != '\0'; i++) {
        for (j = 0; needle[j] != '\0' && haystack[i + j] == needle[j]; j++) {
            if (needle[j + 1] == '\0')
                return (char *)&haystack[i];
        }
    }
    return NULL;
}

// Función para reemplazar $? por el código de salida del último comando
// char *expand_exit_status(char *str, int exit_status) {
//     char *result;
//     char *exit_status_str;
//     char *pos;

//     pos = ft_strstr(str, "$?");
//     if (!pos)
//         return str;

//     exit_status_str = ft_itoa(exit_status);
//     if (!exit_status_str)
//         return str;

//     result = ft_strjoin(ft_substr(str, 0, pos - str), exit_status_str);
//     result = ft_strjoin(result, pos + 2);

//     free(exit_status_str);
//     free(str);

//     return result;
// }

char *expand_exit_status(char *str, int exit_status) {
    char *result = NULL;
    char *exit_status_str;
    char *pos, *prev_pos;

    exit_status_str = ft_itoa(exit_status);
    if (!exit_status_str)
        return str;

    prev_pos = str;
    while ((pos = ft_strstr(prev_pos, "$?")) != NULL) {
        // Concatenar la parte anterior a $?
        if (!result) {
            result = ft_substr(str, 0, pos - str);
        } else {
            char *temp = ft_strjoin(result, ft_substr(prev_pos, 0, pos - prev_pos));
            free(result);
            result = temp;
        }

        // Concatenar el valor de exit_status
        char *temp = ft_strjoin(result, exit_status_str);
        free(result);
        result = temp;

        // Mover el puntero prev_pos después de $?
        prev_pos = pos + 2;
    }

    // Concatenar la parte restante de la cadena
    if (*prev_pos != '\0') {
        char *temp = ft_strjoin(result, prev_pos);
        free(result);
        result = temp;
    }

    free(exit_status_str);
    free(str);

    return result;
}

char *expansor(t_tools *tools)
{
	char *aux;
//	size_t dollar_pos;

	aux = NULL;
	//dollar_pos = dollar_after(tools->arg_str) -1;
	tools->arg_str = expand_exit_status(tools->arg_str, tools->exit_status); 
	

	if (tools->arg_str[dollar_after(tools->arg_str) -2] != '\'' && dollar_after(tools->arg_str) != 0
		&& tools->arg_str[dollar_after(tools->arg_str)] != '\0')
		{
			aux = detect_dollar(tools);
			free(tools->arg_str);
			tools->arg_str = aux;
		}
	//	tools->arg_str = delete_quotes(tools->arg_str, '\"');
	//	tools->arg_str = delete_quotes(tools->arg_str, '\'');

		return (tools->arg_str);
}


char *detect_dollar(t_tools *tools)
{
	int		i;
	char	*aux;
	char	*aux2;
	char	*aux3;

	i = 0;
	aux = ft_strdup("\0");
	while(tools->arg_str[i])
	{
		i += digit_after_dollar(i, tools->arg_str);
                if (tools->arg_str[i] == '$' && tools->arg_str[i + 1] == '?')
                    return (0);
                else if (tools->arg_str[i] == '$' && (tools->arg_str[i + 1] != ' ' &&
                        (tools->arg_str[i + 1] != '"' || tools->arg_str[i + 2] != '\0')) &&
                        tools->arg_str[i + 1] != '\0')
						{
                  			i += loop_dollar(tools, &aux, i);
						}
                else 
                {
                  aux2 = char_to_str(tools->arg_str[i++]);
                  aux3 = ft_strjoin(aux, aux2);
                  free(aux);
                  aux = aux3;
                  free(aux2);
                }
                  
              
	}
        return (aux);

}


int loop_dollar(t_tools *tools, char **aux, int j)
{
  int i;
  int res;
  char *aux2;
  char *aux3;
  int var_length;

  i = 0;
  res = 0;
  var_length = 0;
  while (tools-> envp[i])
  {
    if (ft_strncmp(tools->arg_str + j+ 1, tools->envp[i],
		equal_after(tools->envp[i]) -1) == 0 
		&& after_dollar_lenght(tools->arg_str, j) - j == (int) equal_after(tools->envp[i]))
	{
		aux2 = ft_strdup(tools->envp[i] + equal_after(tools->envp[i]));
		aux3 = ft_strjoin(*aux, aux2);
		free(*aux);
		*aux = aux3;
		free(aux2);
		res = equal_after(tools->envp[i]);
	}
	i++;
  }
  if (res == 0)
  {
	// res = after_dollar_lenght(tools->arg_str, j) -j;
	var_length = after_dollar_lenght(tools->arg_str, j) -j;
	aux2 = strndup(tools->arg_str + j, var_length);
	aux3 = ft_strjoin(*aux, aux2);
	free(*aux);
	*aux = aux3;
	free(aux2);
	res = var_length;
  }
return (res);
}



