
# include "minishell.h"

static int check_file_access_and_open(t_redir *redir) {
    int mode;

    if ((redir->type == 3 && redir->fd != 0) || access(redir->file, F_OK) != -1)
    {
        if (redir->type == 0 || redir->type == 2)
            mode = R_OK;
        else
            mode = R_OK | W_OK;
        if (access(redir->file, mode) != -1)
        {
            if (redir->type == 3)
                mode = O_RDWR | O_APPEND;
            redir->fd = open(redir->file, mode);
        }
        return 1;
    }
    return 0;
}

static int fork_and_run_command(t_command *command, t_tools *tools) {
    int pid;
    int status;

    g_signal = S_CMD;
    pid = fork();
    if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        run_command(command, tools);
        return -1;
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        handle_status(status, tools);
    } else {
        printf("ERROR: fork failed with errno: %d\n", errno);
        return -1;
    }
    return status;
}

int file_open(t_redir *redir) {
    int mode;

    if (check_file_access_and_open(redir))
        return 1;

    if (redir->type == 1 || redir->type == 3) {
        mode = O_CREAT | O_RDWR;
        if (redir->type == 3)
            mode = mode | O_APPEND;
        redir->fd = open(redir->file, mode, S_IRGRP | S_IWUSR | S_IRUSR | S_IROTH);
    } else if (redir->type == 2) {
        return handle_heredoc(redir);
    } else {
        printf("Minishell: %s: File or directory does not exist\n", redir->file);
        return 0;
    }
    return 1;
}


int exec_single_command(t_command *command, t_tools *tools) {
    if (fill_command_from_env(command, tools) == -1)
        return -1;

    if (is_builtin(tools)) {
        ft_builtin(tools);
        return 0;
    }

    return fork_and_run_command(command, tools);
}