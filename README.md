[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/76mHqLr5)

# Description
1. Any command before a '&' symbol runs in background and any command before ';' symbol runs in foreground and command without any symbol in front of it runs in foreground.
2. 'warp' command can be used to change directory just as cd command in linux terminal.
3. 'peek' command can be used to see the contents of a directory which supports -a, -l, -l -a, -a -l, -la, -al flags. -a for displaying hidden files and -l for displaying all details of files. It works exactly like ls command in linux terminal.
4. 'pastevents' command can be used to see the history of recent commands. 'pastevents purge' can be used to delete the history of commands. 'pastevents execute n' can be used to rerun the nth recent command.
5. System commands like sleep, ls, wc, echo, cat, etc. can also be used through this shell.
6. If a foreground process takes more than 2s to run, the next prompt shows the command name and time taken for it to execute.
7. After background process finishes, the shell shows how it ended along with its name and pid.
8. 'proclore' command can be used to obtain information regarding a process like its pid, status, process group, etc.
9. 'seek' command can be used to search for a file or directory. -f flag is there to search for files only, -d flag for directories. There is one more flag -e which changes the directory to the searched directory if only one such directory is found or it prints the searched file name if only one file with the given name is found.
10. This shell supports I/O redirection, i.e., input can be read from a file (using <) and output can be directed to a file (using > or >>).
11. Information about the background processes can be found through 'activities' command. It shows pid, process name and its status for all the background processes.
12. 'ping' command can be used to send signals to processes. Signals like SIGKILL(9),  SIGTSTP(20) can be sent to processes through this command.
13. Ctrl-C sends an interupt to the currently running foreground process by sending it SIGINT signal.
14. Ctrl-D logs out of the shell after killing all the processes.
15. 'fg' command brings any running or background process to foreground and makes its status running.
16. 'bg' command changes the status of stopped background process to running background process.
17. 'neonate' commmand can be used to print the most recently created process after each 'n' seconds where 'n' is given as argument. It stops after pressing the key 'x'.
18. 'iMan' command can be used to fetch and show man pages from the site http://man.he.net/.
19. To run the shell, first run 'make' command in terminal and then run the executable a.out.

# Assumptions
1. For 'pastevents' commands, I am making a file named 'history.txt' in the directory from where th shell is started and maintaining recent history of commands (at max 15 commands) in this file.
2. I have rounded off the time taken for a foreground process to complete in case it runs for more than 2s.
3. Background processes are handled for system commands only.
4. For 'seek' command, files can be searched with or without extensions.
5. 'peek' works with directory paths only.
5. I have not implemented Ctrl-Z, but any running background process can be stopped by sending a SIGTSTP signal through 'ping' command. 
6. In 'iMan' command, I am printing the whole content of the man page.


# Directions for use
1. warp
    warp <path>
2. peek
    peek <flags> <path>
3. proclore
    proclore <pid>
4. seek
    seek <flags> <search> <target_directory>
5. activities
    activities
6. ping
    ping <pid> <signal_number>
7. fg
    fg <pid>
8. bg
    bg <pid>
9. neonate
    neonate -n [time_arg]
10. iMan
    iMan <command_name>