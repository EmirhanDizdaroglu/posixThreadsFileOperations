# Multi-Threaded File Operations

This application demonstrates basic file operations (read, write, open, close) using multi-threading with POSIX threads (`pthread`). The program provides a command-line interface for interacting with files, and each operation is performed by a separate thread.

## Features

- **Read a File**: Read a specified number of characters from a file and print them to the screen.
- **Write to a File**: Write a specified number of bytes from a given string to a file.
- **Open a File**: Check if a file can be opened.
- **Close a File**: Simulate closing a file (the file is actually not opened before this operation).

## Compilation

To compile the program, use the following command:

```bash
gcc -o file_operations file_operations.c -lpthread

## Usage
./file_operations

The program will prompt you to choose an option. Available options are:
1. Read a File: Input the file name and the number of characters to read. The content will be displayed on the screen.
2. Write to a File: Input the file name, number of bytes, and the string to write to the file.
3. Open a File: Input the file name to check if it can be opened.
4. Close a File: Input the file name to simulate closing it.
5. Exit: Exit the program

##Code explanation
Code Explanation
read_file:
Reads a specified number of characters from a file and prints them. It allocates memory for reading and ensures proper error handling.

write_file:
Writes a specified number of bytes from a given string to a file. It checks for errors in opening and writing to the file.

open_file:
Attempts to open a file and reports if it was successful or not. This function is used to simulate the file opening process.

close_file:
Simulates closing a file by opening and closing it. No actual file operations are performed beyond opening and closing the file.

Notes:
The program uses dynamic memory allocation for storing file names and strings. Make sure that input sizes do not exceed allocated memory.
Error handling for file operations includes checking if files can be opened or written to. Ensure that the file paths provided are correct and accessible.
