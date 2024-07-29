#include "proclore.h"

void print_executable_path(char* home, int pid) 
{
    char exePath[256];
    snprintf(exePath, sizeof(exePath), "/proc/%d/exe", pid);

    char exe_path[4096];
    size_t len = readlink(exePath, exe_path, sizeof(exe_path) - 1);

    if (len != -1) {
        exe_path[len] = '\0';
        strcpy(exe_path, exe_path);
    } else {
        perror("Error reading executable path");
        return;
    }

    printf("Executable Path : ");
    int home_len=strlen(home);
    int curr_len=strlen(exe_path);

    if((curr_len>=home_len) && strncmp(home, exe_path, home_len)==0)
    {
        printf("~");
        for(int i=home_len; i<curr_len; i++)
            printf("%c", exe_path[i]);
        printf("\n");
    }
    else
        printf("%s\n", exe_path);
}

int check_foreground_background(int pid)
{
    int flag;      // 0 for foreground and 1 for background 
    int terminal_pgid = tcgetpgrp(STDIN_FILENO); // 0

    if (terminal_pgid == -1)
    {
        perror("Error getting terminal process group ID");
        return 1;
    }

    int pgrp=getpgid(pid);
    if (pgrp == terminal_pgid)
        flag=0;
    else
        flag=1;

    return flag;
}

void proclore(char* home, char* command, int p)
{
    char* pid=strtok(command, " ");
    pid=strtok(NULL, " ");
    if(pid==NULL)
    {
        char ps[10];
        sprintf(ps, "%d", p);
        pid=ps;
    }
    
    char stat_path[256];
    strcpy(stat_path, "/proc/");
    strcat(stat_path, pid);
    strcat(stat_path, "/status");

    FILE *stat_file = fopen(stat_path, "r");
    if (stat_file == NULL) {
        printf("No such process exists\n");
        return;
    }
    
    printf("pid : %s\n", pid);

    char line[256];
    char st;
    char v_mem[20];
    while (fgets(line, sizeof(line), stat_file) != NULL) 
    {
        if (strncmp(line, "State:", 6) == 0) 
        {
            char* state=strtok(line, " ");
            st=state[7];
        }
        else if (strncmp(line, "VmSize:", 7) == 0)
        {
            strcpy(v_mem,strtok(line, " "));
            strcpy(v_mem,strtok(NULL, " "));
        }
    }

    printf("Process Status : %c", st);
    int i_pid=atoi(pid);
    check_foreground_background(i_pid)==0 ? printf("+\n") : printf("\n");
    int gid=getpgid(i_pid);
    printf("Process Group : %d\n", gid);
    printf("Virtual Memory : %s\n", v_mem);

    print_executable_path(home, i_pid);

    fclose(stat_file);
}
