#include "../minishell.h"

void redirections(char *cml) {
    char *token;
    char *delimiters = " ";
    char *saveptr;
    t_commande_line *cmd_line = (t_commande_line *)malloc(sizeof(t_commande_line));
    if (cmd_line == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    cmd_line->fd_in = STDIN_FILENO; // Initialize input file descriptor to stdin
    cmd_line->fd_out = STDOUT_FILENO; // Initialize output file descriptor to stdout

    // Split command line into tokens
    token = strtok_r(cml, delimiters, &saveptr);
    while (token != NULL)
    {
        // Check for redirection tokens
        if (strcmp(token, "<") == 0)
        {
            // Handle input redirection
            token = strtok_r(NULL, delimiters, &saveptr);
            // Update file descriptor for input
            cmd_line->fd_in = open(token, O_RDONLY);
            if (cmd_line->fd_in == -1)
            {
                perror("Error opening input file");
                free(cmd_line); // Free allocated memory before returning
                return;
            }
        } 
        else if (strcmp(token, ">") == 0)
        {
            // Handle output redirection
            token = strtok_r(NULL, delimiters, &saveptr);
            // Update file descriptor for output
            cmd_line->fd_out = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (cmd_line->fd_out == -1)
            {
                perror("Error opening output file");
                free(cmd_line); // Free allocated memory before returning
                return;
            }
        }
        else if (strcmp(token, ">>") == 0)
        {
            // Handle append output redirection
            token = strtok_r(NULL, delimiters, &saveptr);
            // Update file descriptor for output in append mode
            cmd_line->fd_out = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (cmd_line->fd_out == -1)
            {
                perror("Error opening output file in append mode");
                free(cmd_line); // Free allocated memory before returning
                return;
            }
        }
        // Get next token
        token = strtok_r(NULL, delimiters, &saveptr);
    }

    // Store the original file descriptors
    int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);

    // Redirect input and output
    dup2(cmd_line->fd_in, STDIN_FILENO);
    dup2(cmd_line->fd_out, STDOUT_FILENO);

    // Close unnecessary file descriptors
    if (cmd_line->fd_in != STDIN_FILENO)
        close(cmd_line->fd_in);
    if (cmd_line->fd_out != STDOUT_FILENO)
        close(cmd_line->fd_out);

    // Execute the command

    // Restore the original file descriptors
    dup2(original_stdin, STDIN_FILENO);
    dup2(original_stdout, STDOUT_FILENO);

    // Free allocated memory
    free(cmd_line);
    return ;
}
