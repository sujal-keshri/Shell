#include "utilities.h"

ptrnode init_list()
{
    ptrnode head = create_node(0, "first");
    head->last = head;
    return head;
}

ptrnode create_node(int pid, char *command)
{
    ptrnode node_ptr = (ptrnode)malloc(sizeof(node));
    node_ptr->pid = pid;
    node_ptr->command = (char *)malloc(sizeof(char) * 20);
    strcpy(node_ptr->command, command);
    node_ptr->next = NULL;
    node_ptr->last = NULL;
    return node_ptr;
}

void insert_process(ptrnode head, int pid, char *command, int r_s)
{
    ptrnode newnode = create_node(pid, command);
    newnode->r_s_state = r_s;
    head->last->next = newnode;
    head->last = newnode;
}

void search_and_delete(ptrnode head)
{
    ptrnode temp = head;
    while (temp->next != NULL)
    {
        int exited = check_p_status(temp->next->pid, temp->next->command); // 0 if running, 1 if exited
        if (exited == 1)
        {
            ptrnode temp2 = temp->next;
            if (head->last == temp2)
            {
                head->last = temp;
            }
            temp->next = temp2->next;
            free_node(temp2);
        }
        else
            temp = temp->next;
    }
}

int check_p_status(int pid, char *command)
{
    int status;
    int result = waitpid(pid, &status, WNOHANG);

    if (result == -1)
    {
        return 1;
    }
    else if (result != 0)
    {
        if (WIFEXITED(status))
            printf("%s exited normally (%d)\n", command, pid);

        else if (WIFSIGNALED(status))
            printf("%s exited abnormally (%d)\n", command, pid);

        return 1;
    }
    return 0;
}

void free_node(ptrnode node)
{
    free(node->command);
    free(node);
}

void kill_all_processes(ptrnode head)
{
    ptrnode temp = head;
    while (temp->next != NULL)
    {
        kill(temp->next->pid, 9);
        ptrnode temp2 = temp->next;
        if (head->last == temp2)
        {
            head->last = temp;
        }
        temp->next = temp2->next;
        free_node(temp2);
    }
}