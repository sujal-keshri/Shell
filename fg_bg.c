#include "fg_bg.h"

void back_to_fore(char *s_pid)
{
    int i_pid = atoi(s_pid);
    if (kill(i_pid, 0) != 0)
    {
        printf("No such process found\n");
        return;
    }
    if (tcsetpgrp(STDIN_FILENO, getpgid(i_pid)) == -1)
    {
        perror("tcsetpgrp");
        return;
    }

    if (kill(i_pid, SIGCONT) == -1)
    {
        perror("kill");
        return;
    }
    foreground_pid=i_pid;
    fg_running_flag=1;

    search_and_delete(head);

    int status;
    if (waitpid(i_pid, &status, WUNTRACED) == -1)
    {
        perror("waitpid");
        return;
    }
    fg_running_flag=0;
    if (tcsetpgrp(STDIN_FILENO, getpgrp()) == -1)
    {
        perror("tcsetpgrp");
        return;
    }
}

void back_stop_to_running(char *s_pid)
{
    int i_pid = atoi(s_pid);
    if (kill(i_pid, 0) != 0)
    {
        printf("No such process found\n");
        return;
    }
    if (kill(i_pid, SIGCONT) == -1)
    {
        perror("kill");
        return;
    }

    ptrnode temp=head;
    while (temp->next != NULL)
    {
        if (temp->next->pid == i_pid)
        {
            temp->next->r_s_state = 1;
            break;
        }
        temp = temp->next;
    }
}