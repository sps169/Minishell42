
#include "minishell.h"

static int create_pipe(int pipe_fd[2]) {
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return -1;
    }
    return 0;
}

static int read_line_until_delimiter(int write_fd, const char *delimiter) {
    char *line;

    while (1) {
        line = readline("> ");
        if (line == NULL) {
            break; // Fin de la entrada (Ctrl+D)
        }

        if (strcmp(line, delimiter) == 0) {
            free(line);
            break; // Encontrado el delimitador
        }

        write(write_fd, line, strlen(line));
        write(write_fd, "\n", 1);
        free(line);
    }
    return 0;
}

static void redirect_pipe_to_stdin(t_redir *redir, int pipe_fd[2]) {
    close(pipe_fd[1]);
    redir->fd = pipe_fd[0];
}

int handle_heredoc(t_redir *redir) {
    int pipe_fd[2];

    if (create_pipe(pipe_fd) == -1) {
        return -1;
    }

    read_line_until_delimiter(pipe_fd[1], redir->file);
    redirect_pipe_to_stdin(redir, pipe_fd);

    return 1;
}