SimpleShell – Stage 2 User Manual
Name: Serhii Ananiev
Student ID: 39561

DCU Academic Integrity Declaration:
I confirm that this submission is my own work and I have adhered to the DCU Academic Integrity Policy.

------------------------------------------------------------
1. INTRODUCTION
------------------------------------------------------------

SimpleShell is a basic Unix-like command line interpreter written in C.
It supports built-in (internal) commands and external program execution.

The shell displays the current working directory as the command prompt.

2. INTERNAL COMMANDS
------------------------------------------------------------

cd [directory]
    Changes the current directory.
    If no argument is given, prints the current directory.
    Updates the PWD environment variable.

clr
    Clears the terminal screen.

dir [directory]
    Lists files in a directory (similar to: ls -al).

environ
    Displays all environment variables.

echo [text]
    Prints text to the screen.
    Multiple spaces/tabs are reduced to a single space.

help
    Displays this manual using the 'more' filter.

pause
    Pauses the shell until the Enter key is pressed.

quit
    Exits the shell.

------------------------------------------------------------
3. EXTERNAL COMMANDS
------------------------------------------------------------

Any command not recognized as internal is treated as an external program.

Example:
    ls
    gcc main.c
    cat file.txt

The shell creates a child process using fork() and executes the program using execvp().
                
------------------------------------------------------------
4. INPUT/OUTPUT REDIRECTION
------------------------------------------------------------

The shell supports input and output redirection.

Input redirection:
    command < inputfile

Example:
    sort < names.txt

Output redirection:
    command > outputfile
        Creates a file or overwrites it.

    command >> outputfile
        Appends output to an existing file.

Example:
    ls -al > files.txt
    echo hello >> log.txt

Redirection works for both internal and external commands.

------------------------------------------------------------
5. BACKGROUND EXECUTION
------------------------------------------------------------

A command ending with '&' runs in the background.

Example:
    sleep 10 &

The shell does not wait for the process to finish and immediately returns to the prompt.

Foreground execution:
    sleep 10

Background execution:
    sleep 10 &
            
------------------------------------------------------------
6. BATCH MODE
------------------------------------------------------------

The shell can execute commands from a file.

Usage:
    ./simpleshell batchfile.txt

Each line in the file is treated as a command.
The shell exits when the file ends.
    
------------------------------------------------------------
7. ERROR HANDLING
------------------------------------------------------------

The shell handles errors such as:
- Invalid directory in cd
- File not found in redirection
- Command not found
- Failed process creation (fork/exec errors)

Appropriate error messages are displayed to the user.

------------------------------------------------------------
END OF MANUAL
------------------------------------------------------------
