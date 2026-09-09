# SimpleShell

A basic Unix-like command line interpreter written in C, supporting built-in commands, external program execution, I/O redirection, background execution, and batch mode.

## About

SimpleShell mimics the core behavior of a Unix shell: it displays the current working directory as the prompt, interprets built-in commands directly, and delegates anything else to external programs via `fork()` and `execvp()`. Built as part of the Systems Programming module at Dublin City University.

## Features

- **Built-in commands** — `cd`, `clr`, `dir`, `environ`, `echo`, `help`, `pause`, `quit`
- **External command execution** — any command not recognized internally is run as a child process
- **I/O redirection** — supports `<`, `>`, and `>>`
- **Background execution** — commands ending in `&` run without blocking the shell
- **Batch mode** — execute a sequence of commands from a file
- **Error handling** — invalid directories, missing files, unknown commands, and failed process creation are all caught with clear error messages

## Built-in Commands

| Command | Description |
|---|---|
| `cd [directory]` | Changes directory; prints current directory if no argument given. Updates `PWD`. |
| `clr` | Clears the terminal screen. |
| `dir [directory]` | Lists files in a directory (similar to `ls -al`). |
| `environ` | Displays all environment variables. |
| `echo [text]` | Prints text to the screen (collapses repeated whitespace). |
| `help` | Displays the user manual via a `more`-style filter. |
| `pause` | Pauses the shell until Enter is pressed. |
| `quit` | Exits the shell. |

## Usage

### External commands

Any unrecognized command is run as an external program:

```bash
ls
gcc main.c
cat file.txt
```

### I/O redirection

```bash
sort < names.txt        # input redirection
ls -al > files.txt      # output redirection (overwrite)
echo hello >> log.txt   # output redirection (append)
```

Redirection works for both built-in and external commands.

### Background execution

```bash
sleep 10 &   # runs in the background, prompt returns immediately
sleep 10     # runs in the foreground, shell waits
```

### Batch mode

Run a sequence of commands from a file:

```bash
./bin/simpleshell batchfile.txt
```

Each line in the file is treated as a command; the shell exits when the file ends.

## Error Handling

SimpleShell detects and reports:
- Invalid directory in `cd`
- File not found during redirection
- Unknown/unrecognized commands
- Failed process creation (`fork`/`exec` errors)

## Getting Started

### Prerequisites
- GCC or another C compiler
- `make`
- A Unix-like environment (Linux/macOS)

### Build & Run

```bash
git clone https://github.com/Furyzxc/simpleshell.git
cd simpleshell/Stage2
make
./bin/simpleshell
```

### Code explanation

[https://youtu.be/HmjEkYmf1_M](https://youtu.be/HmjEkYmf1_M)

## Author

**Serhii Ananiev**
- Portfolio: [serhii-ananiev.netlify.app](https://serhii-ananiev.netlify.app)
- LinkedIn: [Serhii Ananiev](https://www.linkedin.com/in/serhii-ananiev-267086195/)
- GitHub: [Furyzxc](https://github.com/Furyzxc)
