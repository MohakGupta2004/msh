# msh - Minimal Shell (in C)

## Overview

**`msh`** (short for *Minimal Shell*) is a simple, interactive command-line shell implemented in C. The purpose of this project is to build a minimal shell from scratch, covering basic shell functionalities such as executing commands, managing processes, and handling simple user input/output. This project is designed for learning and understanding the internal workings of a shell, such as process creation, file descriptors, and system calls in a Unix-like operating system.

This project was inspired by the [Codecrafters.io shell tutorial](https://codecrafters.io), where I learned how to implement fundamental shell features and build my own shell step by step.

---

## Features

- **Command Execution**: 
  - Execute system commands using `fork()` and `execvp()`.
  - Supports external commands (e.g., `ls`, `echo`, etc.).
  
- **Built-in Commands**: 
  - Supports built-in commands such as `cd` for changing directories and `exit` for terminating the shell.
  
- **Input Handling**: 
  - Reads user input using `fgets()` and processes it.
  
- **Process Management**: 
  - Executes commands in child processes using `fork()`.
  - Handles waiting for processes to finish using `waitpid()`.
  
- **Pipes and Redirection** (optional):
  - Future support for command piping (`|`) and file input/output redirection (e.g., `command > file.txt`).
  
- **Background Processes**:
  - Run commands in the background using the `&` symbol (e.g., `sleep 10 &`).
  
- **Environment Variables**:
  - Handles environment variables (e.g., `$HOME`, `$PATH`).

---

## Installation

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/yourusername/msh.git
   ```

2. Navigate to the project directory:
   ```bash
   cd msh
   ```

3. Build the shell by compiling the source code:
   ```bash
   make
   ```

4. Run the shell:
   ```bash
   ./msh
   ```

---

## Usage

Once the shell is running, you will see the prompt `msh$`. You can start typing commands just like any other shell.

### Examples

- **Run a command**:
  ```sh
  msh$ ls
  ```
  This will list the files in the current directory.

- **Run a command with arguments**:
  ```sh
  msh$ echo "Hello, World!"
  ```
  This will output `Hello, World!`.

- **Change directories**:
  ```sh
  msh$ cd /path/to/directory
  ```

- **Run a command in the background**:
  ```sh
  msh$ sleep 10 &
  ```

- **Exit the shell**:
  ```sh
  msh$ exit
  ```

---

## How It Works

The shell follows a basic structure to process commands and interact with the user:

1. **Input Handling**: 
   - The shell continuously prompts for user input, reading commands using `fgets()` or `getline()`.

2. **Command Parsing**: 
   - The input is parsed to identify the command and its arguments.

3. **Process Creation**:
   - The shell uses `fork()` to create a child process.
   - In the child process, `execvp()` is used to run the command with arguments.
   - The parent process waits for the child to finish using `waitpid()`.

4. **Built-in Commands**:
   - If the command is a built-in (e.g., `cd`, `exit`), the shell executes it directly without forking a new process.

5. **Background Processes**:
   - If the command includes `&` at the end, the shell creates the child process and does not wait for it to finish.

6. **Error Handling**:
   - The shell handles errors such as command not found or invalid arguments.

---

## Future Features

- **Pipes**: Support for piping commands (e.g., `ls | grep txt`).
- **Redirection**: Support for file redirection (e.g., `command > file.txt` or `command < input.txt`).
- **Job Control**: Add job control to manage background processes.
- **Command History**: Implement command history to store and retrieve previously entered commands.
- **Tab Completion**: Implement basic tab-completion for commands and file paths.
- **Aliases**: Allow users to define custom aliases for commands.

---

## Project Structure

```
msh/
├── msh.c              # Main shell program
├── builtins.c         # Implementation of built-in commands (e.g., cd, exit)
├── utils.c            # Helper functions (e.g., input parsing, process handling)
├── Makefile           # Makefile to build the project
├── README.md          # Project documentation
└── .gitignore         # Git ignore file
```

---

## Contributing

Feel free to fork this project, submit issues, or create pull requests. Contributions to enhance the functionality of the shell are welcome! If you have ideas for new features or improvements, please submit an issue or open a pull request.

---

## License

This project is open-source and available under the MIT License. See the [LICENSE](LICENSE) file for more details.

---

### Acknowledgements

- The `msh` shell project was inspired by the **Codecrafters.io** tutorial series on building a shell in C. It helped me understand key concepts related to system calls, process management, and low-level programming in C.

---

### Final Notes

By building this shell, I gained a deep understanding of how shells work internally and how the operating system handles processes. This project was a great exercise in learning system programming, especially working with processes and system calls in Unix-like systems.

Let me know if you have any suggestions or questions. Happy coding! 🚀
