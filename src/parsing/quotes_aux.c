# include "minishell.h"

size_t quotes_lenght(char *str)
{
  int           i;
  size_t        aux;

  i = 0;
  aux = 0;

  while(str[i])
  {
    if (str[i] == '\'' || str[i] == '\"')
    {
      aux++;
    }
    i++;
  }
  return (aux);
}

char    *delete_quotes(char *str, char c)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while(str[i])
  {
    if (str[i] == c)
    {
      j = 0;
      while(str[i + j] == c)
        j++;
      ft_strlcpy(&str[i], &str[i +j], ft_strlen(str) - i);
    }
    i++;
  }
  return (str);
}
