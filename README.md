# File Management System in C

## Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [Getting Started](#getting-started)
   - [Prerequisites](#prerequisites)
   - [Installation](#installation)
4. [Usage](#usage)
   - [Commands](#commands)
5. [Encryption and Security](#encryption-and-security)
6. [Compression and Decompression](#compression-and-decompression)
7. [Directory Structure](#directory-structure)
8. [Limitations](#limitations)
9. [Future Improvements](#future-improvements)
10. [License](#license)

## Overview

This project is a simple file management system written in C, supporting various file operations including creation, deletion, reading, writing, encryption, decryption, copying, moving, compression, and decompression. The system includes a bash script to provide a command-line interface for interacting with the file management program.

## Features

1. **File Operations**: 
   - Create, delete, read, and write files.
   - Copy and move files within the system.

2. **Security**: 
   - Files can be encrypted and decrypted using XOR encryption to ensure data security.

3. **Compression and Decompression**: 
   - Files can be compressed and decompressed using Run-Length Encoding (RLE).

4. **File Size Information**: 
   - Display the size of a file in bytes.

## Getting Started

### Prerequisites

- A C compiler (e.g., `gcc`)
- Bash shell

### Installation

1. Clone the repository or download the source code.
2. Compile the C program:
   ```bash
   gcc -o file_manager file_manager.c
3. Ensure the bash script (run.sh) is executable:
   ```bash
   chmod +x run.sh
## Usage

1. To start the file management system, run the bash script: 
   ```bash
   ./run.sh
   
## Commands

1. List all files:
   ```bash
   list
   
2. Create a file:
   ```bash
   create <filename>
   
3. Delete a file:
   ```bash
   delete <filename>
   
4. Read a file:
   ```bash
   read <filename>

5. Write to a file:
   ```bash
   write <filename> <content>

6. Encrypt a file:
   ```bash
   encrypt <filename> <password>

7. Decrypt a file:
   ```bash
   decrypt <filename> <password>

8. Copy a file:
   ```bash
   copy <source> <destination>

9. Move a file:
   ```bash
   move <source> <destination>

10. Compress a file:
   ```bash
   compress <filename>
   ```

11. Decompress a file:
   ```bash
   decompress <filename>
   ```

13. Show file size:
   ```bash
   showsize <filename>
   ```

13. Delete Directory:
   ```bash
   delDir
   ```

## Encryption and Security

This system uses XOR encryption for securing files. When a file is encrypted, the XOR operation is performed on the file's content with a given password, and the same operation is used to decrypt it. This simple method provides a basic level of security.

**How XOR Encryption Works:**

- **Encryption**: Each byte of the file's content is XORed with the corresponding byte of the password. If the password is shorter than the content, it is repeated to match the content length.
- **Decryption**: The same XOR operation is applied again using the same password to recover the original content.
- 
## Compression and Decompression

The system uses Run-Length Encoding (RLE) for compressing and decompressing files. This simple compression algorithm is effective for files with many consecutive repeated characters.

**How RLE Compression Works:**

- **Compression**: Consecutive repeated characters in the file are replaced with a single character followed by the number of repetitions.
- **Decompression**: The compressed data is expanded back to its original form by repeating characters according to the counts.

## Directory Structure

- `file_manager.c`: Main source code file for the file management system.
- `run.sh`: Bash script to interact with the file management system.
- `README.md`: This documentation file.

## Limitations

- The current system does not support persistent storage for files beyond the session.
- Limited to a fixed number of files (100 in this implementation).
- Compression is only beneficial for files with many repeated characters.
- XOR encryption provides basic security and is not suitable for protecting sensitive data.

## Future Improvements

- Implement persistent storage to save files beyond the session.
- Add support for additional compression algorithms.
- Enhance encryption methods for better security.
- Improve error handling and input validation.

## Contributing
Contributions are welcome! Please fork the repository and use a feature branch. Pull requests are warmly welcome.
