
#include "minishell.h"

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

char *expand_exit_status(char *str, int exit_status) {
    char *result;
    char *exit_status_str;
    char *pos;

    pos = ft_strstr(str, "$?");
    if (!pos)
        return str;

    exit_status_str = ft_itoa(exit_status);
    if (!exit_status_str)
        return str;

    result = ft_strjoin(ft_substr(str, 0, pos - str), exit_status_str);
    result = ft_strjoin(result, pos + 2);

    free(exit_status_str);
    free(str);

    return result;
}

