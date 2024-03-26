#include "../minishell.h"

void redirections(char *cml) {
    char *token;
    char *delimiters = " \t";
    char *saveptr;
    t_commande_line *cmd_line;

    // Split command line into tokens
    token = strtok_r(cml, delimiters, &saveptr);
    while (token != NULL) {
        // Check for redirection tokens
        if (strcmp(token, "<") == 0)
        {
            // Handle input redirection
            token = strtok_r(NULL, delimiters, &saveptr);
            // Update file descriptor for input
            cmd_line->fd_in = open(token, O_RDONLY);
            if (cmd_line->fd_in == -1) {
                perror("Error opening input file");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(token, ">") == 0) {
            // Handle output redirection
            token = strtok_r(NULL, delimiters, &saveptr);
            // Update file descriptor for output
            cmd_line->fd_out = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (cmd_line->fd_out == -1)
            {
                perror("Error opening output file");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(token, ">>") == 0) {
            // Handle append output redirection
            token = strtok_r(NULL, delimiters, &saveptr);
            // Update file descriptor for output in append mode
            cmd_line->fd_out = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (cmd_line->fd_out == -1)
            {
                perror("Error opening output file in append mode");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(token, "<<") == 0)
        {
            // Handle here document
            // Implement this part based on your requirements
            // You need to read input until a line containing a delimiter is seen
            // and update the file descriptor for input accordingly
        } else
        {
            // Handle other tokens
            // You may need to update other parts of your data structures
            // based on your requirements
        }
        
        // Get next token
        token = strtok_r(NULL, delimiters, &saveptr);
    }
}