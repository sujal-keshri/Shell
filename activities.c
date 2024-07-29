#include "activities.h"

void print_processes(ptrnode head)
{
    ptrnode temp = head;
    while (temp->next != NULL)
    {
        printf("%d : %s - ", temp->next->pid, temp->next->command);
        if(temp->next->r_s_state==1)
            printf("Running\n");
        else if(temp->next->r_s_state==0)
            printf("Stopped\n");
        temp = temp->next;
    }
}