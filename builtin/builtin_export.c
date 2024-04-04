#include "../minishell.h"

char *strtok_custom(char* str, const char* delim) {
    static char* ptr = NULL;
    if (str != NULL)
        ptr = str; // Initialize pointer if a new string is passed
    
    if (ptr == NULL || *ptr == '\0')
        return NULL; // If pointer is NULL or points to end of string, return NULL
    
    char* start = ptr;
    while (*ptr != '\0') {
        const char* d;
        for (d = delim; *d != '\0'; d++) {
            if (*ptr == *d) {
                *ptr = '\0'; // Replace delimiter with NULL terminator
                ptr++;
                return start;
            }
        }
        ptr++;
    }
    return start;
}


int compare(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '=' && b[i] != '=' && a[i] == b[i]) {
        i++;
    }
    if (a[i] == '=' || b[i] == '=') {
        return a[i] - b[i];
    }
    return a[i] - b[i];
}

void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(char **arr, int n) {
    int i = 0;
    while (i < n-1) {
        int j = 0;
        while (j < n-i-1) {
            if (compare(arr[j], arr[j+1]) > 0) {
                swap(&arr[j], &arr[j+1]);
            }
            j++;
        }
        i++;
    }
}

int    add_variable(t_cmd *cmd, int i)
{
    char** new_env;
    int     j;

    new_env = malloc((i + 2) * sizeof(char*)); // Allocate space for the new element and the NULL terminator
    if (new_env == NULL) {
        printf("eroor with alocatting the memory");
        return (1);
    }
    j = 0;
    while (j < i) {
        new_env[j] = cmd->env[j];
        j++;
    }
    new_env[j] = cmd->args;
    j++;
    new_env[j] = NULL;
    cmd->env = new_env;
    return (0);
}


int builtin_export(t_cmd *cmd)
{
    int i = 0;
    while (cmd->env[i] != NULL)
        i++; // Count the number of environment variables
    if (cmd->arg_arr[1] != NULL)
    {
        if(add_variable(cmd, i))
            return(1);
        return(0);
    }
    bubble_sort(cmd->env, i);  // Sort the environment variables

    i = 0;
    while (cmd->env[i] != NULL)
    {  // Print the sorted environment variables
        char* name = strtok_custom(cmd->env[i], "=");
        char* value = strtok_custom(NULL, "=");
        if (value != NULL) {
            printf("declare -x %s=\"%s\"\n", name, value);
        } else {
            printf("declare -x %s=\"\"\n", name);
        }
        i++;
    }
    return (0);
}