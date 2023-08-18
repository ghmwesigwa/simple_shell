# Simple Shell Mini Project

The Simple Shell is a basic Unix-like command-line interpreter implemented in C. It provides users with a minimalistic shell environment to interact with the underlying operating system through command execution, variable substitution, basic I/O redirection, and now, the ability to run commands from a file.

## Features

- **Command Execution**: The shell supports the execution of external commands by utilizing the `execve` system call. Users can run various system utilities, scripts, and programs seamlessly.

- **Built-in Commands**: Essential built-in commands such as `exit` for gracefully terminating the shell session and `env` for displaying environment variables are provided.

- **Variable Substitution**: Users can perform variable substitution by using `$` followed by a variable name (e.g., `$USER`). The shell replaces these placeholders with their corresponding values from the environment.

- **Custom Input Handling**: A custom input reading function with dynamic memory allocation ensures efficient and flexible input processing, accommodating varying command lengths.

- **Basic Error Handling**: Rudimentary error handling offers informative messages for scenarios like command not found or failed process execution.

- **File as Input**: The shell introduces the capability to accept a file as a command line argument. Users can specify a filename as an argument when launching the shell (`./simple_shell filename.txt`). The file should contain commands to be executed, enabling automated execution of multiple commands without requiring user interaction.

## Getting Started

To compile and launch the Simple Shell, follow these instructions:

1. **Clone the Repository**:

    ```bash
    git clone https://github.com/ghmwesigwa/simple-shell.git
    cd simple-shell
    ```

2. **Compile the Source Code**:

    ```bash
    gcc -o simple_shell *.c
    ```

3. **Run the Shell**:

    ```bash
    ./simple_shell
    ```

4. **Run Commands from a File**:

    ```bash
    ./simple_shell filename.txt
    ```

## Usage

Once in the shell environment, interact with the system using various commands:

- Execute an external command:

    ```bash
    ls -l
    ```

- Use built-in commands:

    ```bash
    exit
    env
    ```

- Employ variable substitution:

    ```bash
    $USER
    ```

## Limitations

The Simple Shell project focuses on providing a basic command-line interface and has certain limitations:

- Complex features like pipes, redirects, and advanced scripting are not implemented.
- The shell is designed for educational purposes and may not meet all production use cases.

## Contributing

Contributions are highly encouraged! If you identify bugs, want to extend functionalities, or propose optimizations, please open an issue or submit a pull request. Collaborative efforts are appreciated.

## Acknowledgments

This project was created as part of the ALX Low-Level Programming curriculum.
