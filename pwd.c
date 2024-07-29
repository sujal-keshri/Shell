#include "pwd.h"

char* pwd() {
    size_t size = pathconf(".", _PC_PATH_MAX);

    char* pwd = (char *)malloc((size_t)size);
    getcwd(pwd, size);
    return pwd;
}
