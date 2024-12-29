# msh (Simple Shell)

`msh` is a simple shell program implemented in C that handles basic built-in commands such as `echo`, `exit`, and `type`, along with the ability to execute external commands by searching for them in the system's `PATH`. The shell supports command-line parsing, forking processes, and executing commands.

## Features

- **Built-in Commands**: 
  - `echo`: Prints arguments to the terminal.
  - `exit`: Exits the shell.
  - `type`: Displays the type (built-in or path) of the given command.
  
- **External Command Execution**: 
  - Executes external commands by searching for them in the system's `PATH`.
  - Forks a child process to execute commands.

## Compilation

To compile the program, use the following `gcc` command:

```bash
gcc -o msh main.c
```

This will produce an executable file named `msh`.

## Usage

After compiling the program, you can run the shell by executing the following command in your terminal:

```bash
./msh
```

This will start the interactive shell prompt, where you can type commands.

### Available Commands

1. **`echo <text>`**:
   - Prints the provided text to the console.
   
   Example:
   ```bash
   $ echo Hello World
   Hello World
   ```

2. **`exit`**:
   - Exits the shell.

   Example:
   ```bash
   $ exit
   ```

3. **`type <command>`**:
   - Displays the type of the command (`builtin` or path to the executable).
   
   Example:
   ```bash
   $ type ls
   ls is /bin/ls
   ```

4. **External Commands**:
   - Any other command is treated as an external command. The shell will search for the command in the directories listed in the `PATH` environment variable and execute it if found.
   
   Example:
   ```bash
   $ ls
   ```

### Error Handling

- If a command is not found, the shell will display an error message:
  ```bash
  $ nonexistent_command
  nonexistent_command: command not found
  ```

- If the `type` command is used without any arguments:
  ```bash
  $ type
  type: missing operand
  ```

## License

This project is licensed under the MIT License.

## Contributing

Feel free to fork this repository and submit pull requests with improvements or bug fixes!
