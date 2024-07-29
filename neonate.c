#include "neonate.h"



/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
*/

void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

/**
 * stdout and stdin are buffered we disable buffering on that
 * After entering in raw mode we read characters one by one
 * Up arrow keys and down arrow keys are represented by 3 byte escape codes
 * starting with ascii number 27 i.e. ESC key
 * This way we interpret arrow keys
 * Tabs are usually handled by the term, but here we are simulating tabs for the sake of simplicity
 * Backspace move the cursor one control character to the left
 * @return
*/

int give_latest_pid()
{
    int fin;
    fin=open("/proc/loadavg", O_RDONLY);

    if (fin == -1) 
    {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    char buff[100];
    read(fin, buff, sizeof(buff));
    char* temp=strtok(buff, " ");
    temp=strtok(NULL, " ");
    temp=strtok(NULL, " ");
    temp=strtok(NULL, " ");
    temp=strtok(NULL, " ");
    int latest_pid=atoi(temp);
    return latest_pid;
}


void neonate_exe(char *s_delay)
{
    char ch;
    int i_delay=atoi(s_delay);
    enableRawMode();

    int PID = fork();
    if (PID < 0)
    {
        perror("IN FORK IN NEONATE");
    }
    else if (PID == 0)
    {
        while (1)
        {
            printf("%d\n", give_latest_pid());
            sleep(i_delay);
        }
        exit(0);
    }
    else
    {
        while (1)
        {
            read(STDIN_FILENO, &ch, 1);
            if (ch == 'x')
            {
                kill(PID, SIGTERM);
                wait(NULL);
                break;
            }
        }
    }
    disableRawMode();
}