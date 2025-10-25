# PIPEX

A **Unix command-line tool** built in **C**, designed to replicate **shell pipelines** and reinforce understanding of process management, file descriptors, and inter-process communication. Pipex allows executing commands with redirected input and output, mimicking basic Bash pipeline behavior.

## Features (Mandatory)

- **Command execution** with exactly **2 commands**
- **Input/output redirection** (`<` and `>`)
- **Pipeline** connecting the two commands
- **Error handling** consistent with shell behavior
- **Memory-safe execution** with no leaks

## Features (Bonus)

- **Support for multiple commands** in a pipeline
- **Here-documents** (`<<`) support
- **Enhanced error handling** for edge cases
- **Dynamic number of commands** in the pipeline

## Tech Stack

- **C** – Core language
- **POSIX system calls** – `fork`, `execve`, `pipe`, `dup2`, `wait` etc.
- **Makefile** – For easy build and management

## Installation

1. Clone the repository:

```bash
git clone https://github.com/Felipp3san/pipex.git
cd pipex
```

2. Compile the project:

```bash
make          # Compile mandatory version
make bonus    # Compile bonus version
```

3. Run the executable:

```bash
./pipex file1 cmd1 cmd2 file2        # Mandatory
./pipex file1 cmd1 cmd2 ... cmdn file2  # Bonus
```

## Usage

- **Mandatory (2 commands only):**

```bash
./pipex infile "grep hello" "wc -l" outfile
```
This executes `grep hello < infile | wc -l > outfile`.

- **Bonus (multiple commands):**

```bash
./pipex input.txt "cat" "grep data" "sort" output.txt
```

- **Bonus: Here-document:**

```bash
./pipex here_doc LIMITER "cat" "wc -l" outfile
```
Allows input until `LIMITER` is reached.

## Compilation

- Build the mandatory executable:

```bash
make
```

- Build the bonus executable:

```bash
make bonus
```

- Remove object files:

```bash
make clean
```

- Remove all binaries and rebuild:

```bash
make re
```

## License

Educational project under 42 School academic policy.
