#include "io_redirection.h"

io_return check_and_redirect(char *command)
{
    io_return ret;
    
    char temp_command[512];
    strcpy(temp_command, command);
    ret.in_flag=0;
    ret.out_flag=0;

    char *temp;
    if (strstr(command, ">>"))
    {
        ret.out_flag=1;
        if (strstr(command, "<"))
        {
            ret.in_flag=1;
            temp = strtok(temp_command, "<");
            strcpy(ret.command_part, temp);
            remove_whitespaces(ret.command_part);
            temp = strtok(NULL, ">>");
            strcpy(ret.in_file, temp);
            remove_whitespaces(ret.in_file);
            temp = strtok(NULL, ">>");
            strcpy(ret.out_file, temp);
            remove_whitespaces(ret.out_file);
        }
        else
        {
            temp = strtok(temp_command, ">>");
            strcpy(ret.command_part, temp);
            remove_whitespaces(ret.command_part);
            temp = strtok(NULL, ">>");
            strcpy(ret.out_file, temp);
            remove_whitespaces(ret.out_file);
        }
    }
    else if (strstr(command, ">"))
    {
        ret.out_flag=2;
        if (strstr(command, "<"))
        {
            ret.in_flag=1;
            temp = strtok(temp_command, "<");
            strcpy(ret.command_part, temp);
            remove_whitespaces(ret.command_part);
            temp = strtok(NULL, ">");
            strcpy(ret.in_file, temp);
            remove_whitespaces(ret.in_file);
            temp = strtok(NULL, ">");
            strcpy(ret.out_file, temp);
            remove_whitespaces(ret.out_file);
        }
        else
        {
            temp = strtok(temp_command, ">");
            strcpy(ret.command_part, temp);
            remove_whitespaces(ret.command_part);
            temp = strtok(NULL, ">");
            strcpy(ret.out_file, temp);
            remove_whitespaces(ret.out_file);
        }
    }
    else if (strstr(command, "<"))
    {
        ret.in_flag=1;
        temp = strtok(temp_command, "<");
        strcpy(ret.command_part, temp);
        remove_whitespaces(ret.command_part);
        temp = strtok(NULL, "<");
        strcpy(ret.in_file, temp);
        remove_whitespaces(ret.out_file);
    }
    return ret;
}