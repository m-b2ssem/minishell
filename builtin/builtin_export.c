#include "../minishell.h"

/*void free_env_list(t_env *env)
{
    t_env *temp;

    while (env != NULL) {
        temp = env;
        env = env->next;
        free(temp->name);
        free(temp->value);
        free(temp);
    }
}*/

t_env *copy_env_list(t_env *env) {
    t_env *new_env;
    t_env *temp;

    if (env == NULL)
        return (NULL);
    new_env = NULL;
    while (env != NULL)
    {
        temp = (t_env *)malloc(sizeof(t_env));
        if (!temp)
            return (free_list(&new_env), NULL);
        temp->name = env->name ? strdup(env->name) : strdup("");
        temp->value = env->value ? strdup(env->value) : strdup("");
        temp->export = env->export;
        temp->next = new_env;
        new_env = temp;
        env = env->next;
    }
    return new_env;
}

void swap(t_env *a, t_env *b)
{
    char *temp_name;
    char *temp_value;
    int temp_export;

    temp_name = strdup(a->name);
    temp_value = strdup(a->value);
    temp_export = a->export;

    free(a->name);
    free(a->value);
    a->name = strdup(b->name);
    a->value = strdup(b->value);
    a->export = b->export;

    free(b->name);
    free(b->value);
    b->name = temp_name;
    b->value = temp_value;
    b->export = temp_export;
}

void bubble_sort(t_env **head)
{
    int swapped = 1;
    t_env *ptr1;
    t_env *lptr = NULL;

    /* Checking for empty list */
    if (*head == NULL)
        return;

    while (swapped)
    {
        swapped = 0;
        ptr1 = *head;
        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->name, ptr1->next->name) > 0) { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
}

int    add_variable(t_cmd *cmd)
{
    int     i;
    int     j;
    int     export;
    char    *name;
    char    *value;
    t_env   *new;

    i = 1;
    name = malloc(sizeof(char) * (strlen(cmd->arg_arr[i]) + 1));
    if (!name)
        return (1);  // Error allocating memory for new environment variable
    value = malloc(sizeof(char) * (strlen(cmd->arg_arr[i]) + 1));
    if (!value)
        return (free(name), 1);  // Error allocating memory for new environment variable
    while(cmd->arg_arr[i] != NULL)
    {
        j = 0;
        while (cmd->arg_arr[i][j] != '=' && cmd->arg_arr[i][j] != '\0')
        {
            name[j] = cmd->arg_arr[i][j];
            j++;
        }
        name[j] = '\0';
        if (cmd->arg_arr[i][j] == '=')
        {
            export = 1;
            j++;
            while (cmd->arg_arr[i][j] != '\0')
            {
                value[j] = cmd->arg_arr[i][j];
                j++;
            }
            value[j] = '\0';
        }
        else
        {
            export = 0;
            value = "";
        }
        new = lst_new(name, value, new, export);
        if (!new)
            return (1);  // Error allocating memory for new environment variable
        lst_addback(&cmd->env, new);
        //free(name);
        //free(value);
        i++;
    }
    free(name);
    free(value);
    return (0);
}


int builtin_export(t_cmd *cmd)
{
    t_env *temp = NULL;
    t_env *head = NULL;

    if (cmd->arg_arr[1] != NULL)
    {
        if(add_variable(cmd))
                return(1);
        return(0);
    }
    temp = copy_env_list(cmd->env);
    if (!temp)
        return (1);/// Error copying environment variables
    head = temp; // Keep a reference to the head of the list
    bubble_sort(&temp);  // Sort the environment variables
    while (temp != NULL)
    {
        if (temp->export == 1)
        {
            printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
        }
        temp = temp->next;
    }
    free_list(&head); // Free the head of the list
    return (0);
}