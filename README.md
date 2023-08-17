# Simple Shell Mini Project

The Simple Shell Mini Project is a minimalistic Unix-like command-line interpreter implemented in C. It offers users a basic shell environment to interact with the underlying operating system through command execution, variable substitution, and basic I/O redirection.

## Features

- **Command Execution**: The shell provides the ability to execute external commands by utilizing the `execve` system call. Users can run various system utilities, scripts, and programs seamlessly.

- **Built-in Commands**: The shell supports essential built-in commands such as `exit` to gracefully terminate the shell session and `env` to display the current environment variables.

- **Variable Substitution**: Users can employ variable substitution by prefixing variable names with the `$` symbol (e.g., `$USER`). The shell replaces these placeholders with their respective values from the environment.

- **Custom Input Handling**: The shell employs a custom input reading function with dynamic memory allocation. This ensures efficient and flexible input processing, accommodating varying command lengths.

- **Basic Error Handling**: The shell incorporates rudimentary error handling, offering informative error messages for scenarios like command not found or failed process execution.

## Getting Started

To compile and launch the simple shell, adhere to the following instructions:

1. **Clone the Repository**:

    ```bash
    git clone https://github.com/ghmwesigwa/simple-shell.git
    cd simple-shell
    ```

2. **Compile the Source Code**:

    ```bash
    gcc -o shell shell.c replace_variables.c print_environment.c handle_exit.c
    ```

3. **Run the Shell**:

    ```bash
    ./shell
    ```

## Usage

Once within the shell environment, users can interact with the system using various commands. Here are some examples:

- Execute an external command:

    ```bash
    ls -l
    ```

- Utilize built-in commands:

    ```bash
    exit
    env
    ```

- Employ variable substitution:

    ```bash
    $USER
    ```

## Contributing

Contributions to this simple shell mini project are wholeheartedly encouraged! If you identify any bugs, wish to extend functionalities, or propose optimizations, please open an issue or submit a pull request. Constructive collaboration is greatly appreciated.


## Acknowledgments

This project draws inspiration from the simplicity and power of traditional Unix shells. We extend our gratitude to the contributors.

