#include "minishell.h"



char *get_right_str(char *str, int pos)
{
    char *res;
    int i = 0;
    int lon_str = ft_strlen(str);
    int lon = ft_strlen(str) - pos;

    res = ft_calloc(lon, sizeof(char));
    i = pos;
    int j = 0;
    while (i < lon_str)
    {
        res[j] = str[i];
        i++;
        j++;
    }
    res[i] = '\0';
    return (res);
}

char *get_left_str(char *str, int pos)
{
    char *res;
    int i;

    res = ft_calloc(pos, sizeof(char));
    i = 0;

    while(i < pos)
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);

}


int get_char_pos(char *s, char c)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == c)
            return (i);

        i++;
    }   
    return (0);
}


int if_var(char *str)
{
    char **split = split_minishell(str, ' ');
    int i = 0;
    while (split[i])
    {
        printf("%s\n", split[i]);
        i++;
    }
    return (0);
}




