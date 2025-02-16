# **Efficient File Management System in C** 🚀

## 📌 **Table of Contents**  

1. [Overview](#overview)  
2. [Features](#features)  
3. [Getting Started](#getting-started)  
   - [Prerequisites](#prerequisites)  
   - [Installation](#installation)  
4. [Usage](#usage)  
   - [Commands](#commands)  
5. [Encryption & Security](#encryption--security)  
6. [Compression & Decompression](#compression--decompression)  
7. [Directory Structure](#directory-structure)  
8. [Contributing](#contributing)  

---

## 📖 **Overview**  
The **Efficient File Management System in C** is a high-performance, CLI-based file manager designed for **Unix/Linux environments**. It leverages **low-level system calls**, **multi-threading**, and **memory-mapped I/O** for **fast and efficient file operations**. 

Key functionalities include **encryption, compression, and decompression**, ensuring security and optimized storage. A **Bash-integrated CLI tool** is provided for seamless automation and ease of use.

---

## ✨ **Features**  

✅ **Comprehensive File Operations**: Create, delete, read, write, copy, and move files efficiently.  
✅ **Multi-Threaded Processing**: Enhances performance and responsiveness.  
✅ **Advanced Security**: AES-based encryption/decryption for file protection.  
✅ **Compression & Decompression**: Supports efficient RLE compression.  
✅ **Optimized for Unix/Linux**: Utilizes POSIX APIs and system calls.  
✅ **Bash Integration**: Automates command-line file management.  

---

## 🚀 **Getting Started**  

### 🔧 **Prerequisites**  
Ensure you have the following installed on your system:
- **C Compiler** (e.g., `gcc`)
- **Bash Shell** (for script execution)

### 📥 **Installation**  
1. **Clone the repository**:  
   ```bash
   git clone https://github.com/duanepm/File-Management-System-in-C.git
   ```  
2. **Compile the C program**:  
   ```bash
   gcc -o file_manager file_manager.c -pthread
   ```  
3. **Ensure the Bash script is executable**:  
   ```bash
   chmod +x run.sh
   ```  

---

## 📌 **Usage**  
Run the file management system:
```bash
./run.sh
```

### 🛠 **Commands**  

| Command | Description |
|---------|-------------|
| `list` | Lists all files in the directory |
| `create <filename>` | Creates a new file |
| `delete <filename>` | Deletes a file |
| `read <filename>` | Displays file content |
| `write <filename> <content>` | Writes content to a file |
| `encrypt <filename> <password>` | Encrypts a file using AES-based encryption |
| `decrypt <filename> <password>` | Decrypts an encrypted file |
| `copy <source> <destination>` | Copies a file to a new location |
| `move <source> <destination>` | Moves a file |
| `compress <filename>` | Compresses a file using RLE |
| `decompress <filename>` | Decompresses a file |
| `showsize <filename>` | Displays file size |

---

## 🔒 **Encryption & Security**  
This system implements **AES-based encryption** for securing files, ensuring that sensitive data remains protected from unauthorized access.  

---

## 📦 **Compression & Decompression**  
Utilizes **Run-Length Encoding (RLE)** to optimize file storage, making it efficient for compressing repetitive data patterns.  

---

## 📂 **Directory Structure**  
```
📁 File-Management-System-in-C/
├── 📜 file_manager.c    # Main C program
├── 📜 run.sh            # Bash script for CLI interaction
├── 📜 README.md         # Documentation
```

---

## 🤝 **Contributing**  
Contributions are welcome! To contribute:
1. **Fork the repository**
2. **Create a feature branch**
3. **Submit a pull request** 🚀  

💡 Feel free to raise issues or suggest improvements!

---

🔗 **License**: This project is licensed under the **MIT License**. 

🌟 **Star this repository if you found it helpful!** ⭐
