#include "signals.h"

void send_signal(char *pid, char *sig_num)
{
    int i_pid = atoi(pid);
    int i_sig_num = (atoi(sig_num));
    i_sig_num = i_sig_num % 32;

    if (kill(i_pid, 0) == -1)
    {
        printf("No such process exists\n");
        return;
    }

    if (kill(i_pid, i_sig_num) == -1)
    {
        printf("Failed to send signal to the process\n");
        return;
    }

    else if (i_sig_num==20 || i_sig_num==19)
    {
        ptrnode temp=head;
        while(temp->next!=NULL)
        {
            if (temp->next->pid==i_pid)
            {
                temp->next->r_s_state=0;
                break;
            }
            temp=temp->next;
        }
    }

    printf("Sent signal %d to process with pid %d\n", i_sig_num, i_pid);

    return;
}

void ctrl_c_func(int signal)
{
    if (foreground_pid > 0)
    {
        printf("\n");
        kill(foreground_pid, SIGINT);
        foreground_pid = 0;
    }
    else if (fg_running_flag == 0)
    {
        printf("\n");
        prompt(home, prompt_input);
        fflush(stdout);
    }
}