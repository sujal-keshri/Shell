#include "prompt.h"

void prompt(char* home, char* prompt_input) {
    // Do not hardcode the prmopt
    // printf("<Everything is a file> ");

    char *username = getlogin();
    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    printf("<");
    printf(BOLD_TEXT GREEN_COLOR "%s@%s" RESET_COLOR RESET_FORMAT, username, hostname);
    printf(":");

    char* curr_dir=pwd();
    int home_len=strlen(home);
    int curr_len=strlen(curr_dir);

    if(strcmp(home, curr_dir)==0)
        printf(BOLD_TEXT BLUE_COLOR "~" RESET_COLOR RESET_FORMAT);
    else if((curr_len>=home_len) && strncmp(home, curr_dir, home_len)==0)
    {
        printf(BOLD_TEXT BLUE_COLOR "~" RESET_COLOR RESET_FORMAT);
        for(int i=home_len; i<curr_len; i++)
            printf( BOLD_TEXT BLUE_COLOR "%c" RESET_COLOR RESET_FORMAT, curr_dir[i]);
    }
    else
        printf(BOLD_TEXT BLUE_COLOR "%s" RESET_COLOR RESET_FORMAT, curr_dir);

    printf("%s", prompt_input);
    printf("> ");
}
