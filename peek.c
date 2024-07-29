#include "peek.h"

char *give_entry_path(char *dir_path, char *entry_name)
{
    char *entry_path = (char *)malloc(sizeof(char) * 1000);
    strcpy(entry_path, dir_path);
    strcat(entry_path, "/");
    strcat(entry_path, entry_name);
    return entry_path;
}

list give_list(char *dir_path)
{
    struct dirent **entry_list;
    int num_entry = scandir(dir_path, &entry_list, NULL, NULL); // alphasort
    return entry_list;
}

struct stat give_stat(char *entry_path)
{
    struct stat entry_info;
    stat(entry_path, &entry_info);
    return entry_info;
}

int entry_type(struct stat entry_info)
{
    int type;                           // 1 for executables, 2 for regular files and 3 for directories
    if (S_ISDIR(entry_info.st_mode))
        type = 3;

    else if (entry_info.st_mode & S_IXUSR)
        type = 1;

    else if (S_ISREG(entry_info.st_mode))
        type = 2;

    return type;
}

char *permission(char *entry_path)
{
    struct stat entry_info = give_stat(entry_path);
    char *perm = (char *)malloc(sizeof(char) * 20);
    perm[0] = entry_type(entry_info) == 3 ? 'd' : '-';
    perm[1] = entry_info.st_mode & S_IRUSR ? 'r' : '-';
    perm[2] = entry_info.st_mode & S_IWUSR ? 'w' : '-';
    perm[3] = entry_info.st_mode & S_IXUSR ? 'x' : '-';
    perm[4] = entry_info.st_mode & S_IRGRP ? 'r' : '-';
    perm[5] = entry_info.st_mode & S_IWGRP ? 'w' : '-';
    perm[6] = entry_info.st_mode & S_IXGRP ? 'x' : '-';
    perm[7] = entry_info.st_mode & S_IROTH ? 'r' : '-';
    perm[8] = entry_info.st_mode & S_IWOTH ? 'w' : '-';
    perm[9] = entry_info.st_mode & S_IXOTH ? 'x' : '-';
    return perm;
}

void print_entry_name(char *entry, char *entry_path)
{
    struct stat entry_info;
    if (stat(entry_path, &entry_info) != 0)
    {
        perror("Error getting file information");
        return;
    }

    int type = entry_type(entry_info);
    if (type == 1)
        printf(GREEN_COLOR BOLD_TEXT "%s\n" RESET_COLOR RESET_FORMAT, entry);

    else if (type == 2)
        printf("%s\n", entry);

    else if (type == 3)
        printf(BLUE_COLOR BOLD_TEXT "%s\n" RESET_COLOR RESET_FORMAT, entry);
}

void print_entry_info(char *entry, char *entry_path)
{
    struct stat entry_info;
    if (stat(entry_path, &entry_info) != 0)
    {
        perror("Error");
        return;
    }

    struct passwd *user = getpwuid(entry_info.st_uid);
    struct group *group = getgrgid(entry_info.st_gid);

    // printPermissions(entry_info.st_mode);
    char *permsn = permission(entry_path);
    printf("%s", permsn);
    free(permsn);

    printf(" %2ld ", (long)entry_info.st_nlink);

    printf("%-8s ", user->pw_name);
    printf("%-8s ", group->gr_name);

    printf("%8lu ", (unsigned long)entry_info.st_size);

    char dateStr[20];
    strftime(dateStr, sizeof(dateStr), "%b %d %H:%M", localtime(&entry_info.st_mtime));
    printf("%s ", dateStr);

    print_entry_name(entry, entry_path);
}

void print_dir(char *home, char *previous_directory, char *command, int flag)
{
    char *dir_path = strtok(command, " ");
    dir_path = strtok(NULL, " ");
    if (flag == 1)
        dir_path = strtok(NULL, " ");

    if (dir_path == NULL)
        dir_path = ".";
    else if (strcmp(dir_path, "~")==0)
        dir_path=home;
    else if (strcmp(dir_path, "-")==0)
    {
        if (strcmp(previous_directory, "OLD DIRECTORY NOT SET")==0)
        {
            printf("OLD DIRECTORY NOT SET\n");
            return;
        }
        else
            dir_path=previous_directory;
    }

    struct dirent **entry_list;
    int num_entry = scandir(dir_path, &entry_list, NULL, alphasort); // alphasort
    if (num_entry < 0)
    {
        perror("Error");
        return;
    }

    for (int i = 0; i < num_entry; i++)
    {
        if (flag == 1 || (flag == 0 && entry_list[i]->d_name[0] != '.'))
        {
            char *entry_path = give_entry_path(dir_path, entry_list[i]->d_name);
            print_entry_name(entry_list[i]->d_name, entry_path);
            free(entry_path);
        }
        free(entry_list[i]);
    }
    free(entry_list);
}

void print_l_dir(char *home, char *previous_directory, char *command, int flag)
{
    char *dir_path = strtok(command, " ");
    dir_path = strtok(NULL, " ");
    dir_path = strtok(NULL, " ");

    if(dir_path!=NULL && (strcmp(dir_path, "-a")==0 || strcmp(dir_path, "-l")==0))
        dir_path=strtok(NULL, " ");
        
    if (dir_path == NULL)
        dir_path = ".";
    else if (strcmp(dir_path, "~")==0)
        dir_path=home;
    else if (strcmp(dir_path, "-")==0)
    {
        if (strcmp(previous_directory, "OLD DIRECTORY NOT SET")==0)
        {
            printf("OLD DIRECTORY NOT SET\n");
            return;
        }
        else
            dir_path=previous_directory;
    }

    struct dirent **entry_list;
    int num_entry = scandir(dir_path, &entry_list, NULL, alphasort); // alphasort
    if (num_entry < 0)
    {
        perror("Error");
        return;
    }

    for (int i = 0; i < num_entry; i++)
    {
        if (flag == 1 || (flag == 0 && entry_list[i]->d_name[0] != '.'))
        {
            char *entry_path = give_entry_path(dir_path, entry_list[i]->d_name);
            print_entry_info(entry_list[i]->d_name, entry_path);
            free(entry_path);
        }
        free(entry_list[i]);
    }
    free(entry_list);
}

void peek(char *home, char *previous_directory, char *command)
{
    char *l = strstr(command, "-l");
    char *a = strstr(command, "-a");
    char *la = strstr(command, "-la");
    char *al = strstr(command, "-al");

    if (la != NULL || al != NULL || (l != NULL && a != NULL))
        print_l_dir(home, previous_directory, command, 1);

    else if (l == NULL && a == NULL)
        print_dir(home, previous_directory, command, 0);

    else if (l == NULL && a != NULL)
        print_dir(home, previous_directory, command, 1);

    else if (l != NULL && a == NULL)
        print_l_dir(home, previous_directory, command, 0);
}