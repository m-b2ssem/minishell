#include "../minishell.h"


t_env *copy_env_list(t_env *env) {
    t_env *new_env;
    t_env *temp;

    if (env->next == NULL)
        return (NULL);

    new_env = NULL;
    while (env != NULL)
    {
        temp = (t_env *)malloc(sizeof(t_env));
        if (!temp)
            return (free_list(&new_env), NULL);
        temp->name = env->name ? strdup(env->name) : strdup(" ");
        temp->value = env->value ? strdup(env->value) : strdup(" ");
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

int search_if_variable_exist(t_cmd *cmd, char *name)
{
    t_env *temp = cmd->env;

    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            return (1);
        }
        temp = temp->next;
    }
    return (0);
}

void return_name(char *arg, char **name)
{
    int i = 0;

    while (arg[i] != '=' && arg[i] != '\0')
    {
        (*name)[i] = arg[i];
        i++;
    }
    (*name)[i] = '\0';
}

int return_value(char *arg, char **value)
{
    int i = 0;
    int j = 0;
    int export = 0;

    while (arg[i] != '=' && arg[i] != '\0')
    {
        i++;
    }
    if (arg[i] == '\0')
    {
        (*value)[j] = ' ';
        (*value)[j + 1] = '\0';
        return (export);
    }
    i++;
    while (arg[i] != '\0')
    {
        export = 1;
        (*value)[j] = arg[i];
        i++;
        j++;
    }
    (*value)[j] = '\0';
    return (export);
}

void update_value(t_cmd *cmd, char *name, char *value, int export)
{
    t_env *temp = cmd->env;

    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            free(temp->value);
            temp->value = strdup(value);
            temp->export = export;
            break;
        }
        temp = temp->next;
    }
}

int    add_variable(t_cmd *cmd)
{
    int     i;
    int     export;
    char    *name;
    char    *value;
    t_env   *new;


    i = 1;
   name = ft_calloc(sizeof(char) ,(strlen(cmd->arg_arr[i]) + 1));
   if (!name)
   	return (1);
   value = ft_calloc(sizeof(char) ,(strlen(cmd->arg_arr[i]) + 1));
   if (!value)
   	return (free(name), 1);
    while(cmd->arg_arr[i] != NULL)
    {
        return_name(cmd->arg_arr[i], &name);
        export = return_value(cmd->arg_arr[i], &value);
        if (search_if_variable_exist(cmd, name))
        {
            update_value(cmd, name, value, export);
        }
        else
        {
            new = lst_new(name, value, new, export);
            if (!new)
                return (free(name), free(value), 1);
            lst_addback(&cmd->env, new);
        }
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
        return (1);
    head = temp;
    bubble_sort(&temp);
    while (temp != NULL)
    {
        if (temp->export == 1)
        {
            printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
        }
        temp = temp->next;
    }
    free_list(&head);
    return (0);
}
