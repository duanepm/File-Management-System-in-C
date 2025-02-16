#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define MAX_FILES 100
#define MAX_FILE_NAME 100
#define MAX_FILE_CONTENT 1000
#define MAX_PASSWORD_LENGTH 50

struct File 
{
    char name[MAX_FILE_NAME];
    char content[MAX_FILE_CONTENT];
    int size;
    int isOccupied;
    int isEncrypted;
    char password[MAX_PASSWORD_LENGTH];
};

struct File files[MAX_FILES];

int isFileOperationAllowed(int fileIndex) 
{
    if (files[fileIndex].isEncrypted) {
        printf("File '%s' is encrypted. File operations are locked.\n", files[fileIndex].name);
        return 0;
    }
    return 1;
}

void initializeFileSystem() 
{
    for (int i = 0; i < MAX_FILES; ++i) {
        files[i].isOccupied = 0;
        files[i].isEncrypted = 0;
    }
}

void createFile(const char *filename) 
{
    int availableIndex = -1;

    for (int i = 0; i < MAX_FILES; ++i) {
        if (files[i].isOccupied == 0) {
            availableIndex = i;
            break;
        }
    }

    if (availableIndex == -1) {
        printf("No space available to create file '%s'.\n", filename);
        return;
    }

    for (int i = 0; i < MAX_FILES; ++i) {
        if (files[i].isOccupied == 1 && strcmp(files[i].name, filename) == 0) {
            printf("File '%s' already exists. Cannot create.\n", filename);
            return;
        }
    }

    strcpy(files[availableIndex].name, filename);
    files[availableIndex].size = 0;
    files[availableIndex].isOccupied = 1;
    files[availableIndex].isEncrypted = 0;

    printf("File '%s' created.\n", filename);
}

void deleteFile(const char *filename) 
{
    int fileIndex = -1;

    for (int i = 0; i < MAX_FILES; ++i) {
        if (files[i].isOccupied == 1 && strcmp(files[i].name, filename) == 0) {
            fileIndex = i;
            break;
        }
    }

    if (fileIndex == -1) {
        printf("File '%s' not found. Cannot delete.\n", filename);
        return;
    }

    if (files[fileIndex].isEncrypted) {
        printf("File '%s' is encrypted. Cannot delete an encrypted file.\n", filename);
        return;
    }

    files[fileIndex].isOccupied = 0;
    memset(files[fileIndex].name, 0, sizeof(files[fileIndex].name));
    memset(files[fileIndex].content, 0, sizeof(files[fileIndex].content));
    files[fileIndex].size = 0;

    printf("File '%s' deleted.\n", filename);
}

void xorEncryptDecrypt(char *data, const char *key, int dataLength) {
    int keyLength = strlen(key);
    for (int i = 0; i < dataLength; i++) {
        data[i] ^= key[i % keyLength];
    }
}

unsigned char aes_key[AES_KEY_SIZE / 8] = "0123456789abcdef0123456789abcdef";

void encryptAES(const unsigned char *input, unsigned char *output, int length) {
    AES_KEY enc_key;
    AES_set_encrypt_key(aes_key, AES_KEY_SIZE, &enc_key);
    AES_encrypt(input, output, &enc_key);
}

void decryptAES(const unsigned char *input, unsigned char *output) {
    AES_KEY dec_key;
    AES_set_decrypt_key(aes_key, AES_KEY_SIZE, &dec_key);
    AES_decrypt(input, output, &dec_key);
}

void readFile(const char *filename) 
{
    int fileIndex = -1;

    for (int i = 0; i < MAX_FILES; ++i) {
        if (files[i].isOccupied == 1 && strcmp(files[i].name, filename) == 0) {
            fileIndex = i;
            break;
        }
    }

    if (fileIndex == -1) {
        printf("File '%s' not found. Cannot read.\n", filename);
        return;
    }

    if (files[fileIndex].isEncrypted) {
        printf("File '%s' is encrypted. Cannot read an encrypted file.\n", filename);
        return;
    }

    printf("Content of file '%s':\n%s\n", filename, files[fileIndex].content);
}

void writeFile(const char *filename, const char *content) 
{
    int fileIndex = -1;

    for (int i = 0; i < MAX_FILES; ++i) {
        if (files[i].isOccupied == 1 && strcmp(files[i].name, filename) == 0) {
            fileIndex = i;
            break;
        }
    }

    if (fileIndex == -1) {
        printf("File '%s' not found. Cannot write.\n", filename);
        return;
    }

    if (files[fileIndex].isEncrypted) {
        printf("File '%s' is encrypted. Cannot write to an encrypted file.\n", filename);
        return;
    }

    strcpy(files[fileIndex].content, content);
    files[fileIndex].size = strlen(content);

    printf("Content written to file '%s'.\n", filename);
}

void copyFile(const char *source, const char *destination) 
{
    int sourceIndex = -1;
    int destinationIndex = -1;

    for (int i = 0; i < MAX_FILES; ++i) {
        if (files[i].isOccupied == 1 && strcmp(files[i].name, source) == 0) {
            sourceIndex = i;
        }
        if (files[i].isOccupied == 0 && destinationIndex == -1) {
            destinationIndex = i;
        }
        if (files[i].isOccupied == 1 && strcmp(files[i].name, destination) == 0) {
            printf("Destination file '%s' already exists. Cannot copy.\n", destination);
            return;
        }
    }

    if (sourceIndex == -1) {
        printf("Source file '%s' not found. Cannot copy.\n", source);
        return;
    }

    if (destinationIndex == -1) {
        printf("No space available for the destination file '%s'. Cannot copy.\n", destination);
        return;
    }

    if (files[sourceIndex].isEncrypted) {
        printf("Source file '%s' is encrypted. Cannot copy encrypted file.\n", source);
        return;
    }

    strcpy(files[destinationIndex].name, destination);
    strcpy(files[destinationIndex].content, files[sourceIndex].content);
    files[destinationIndex].size = files[sourceIndex].size;
    files[destinationIndex].isOccupied = 1;
    files[destinationIndex].isEncrypted = 0; 

    printf("File '%s' copied to '%s'.\n", source, destination);
}

void moveFile(const char *source, const char *destination) 
{
    int sourceIndex = -1;
    int destinationIndex = -1;

    for (int i = 0; i < MAX_FILES; ++i) {
        if (files[i].isOccupied == 1 && strcmp(files[i].name, source) == 0) {
            sourceIndex = i;
        }
        if (files[i].isOccupied == 0 && destinationIndex == -1) {
            destinationIndex = i;
        }
        if (files[i].isOccupied == 1 && strcmp(files[i].name, destination) == 0) {
            printf("Destination file '%s' already exists. Cannot move.\n", destination);
            return;
        }
    }

    if (sourceIndex == -1) {
        printf("Source file '%s' not found. Cannot move.\n", source);
        return;
    }

    if (destinationIndex == -1) {
        printf("No space available for the destination file '%s'. Cannot move.\n", destination);
        return;
    }

    if (files[sourceIndex].isEncrypted) {
        printf("Source file '%s' is encrypted. Cannot move encrypted file.\n", source);
        return;
    }

    strcpy(files[destinationIndex].name, destination);
    strcpy(files[destinationIndex].content, files[sourceIndex].content);
    files[destinationIndex].size = files[sourceIndex].size;
    files[destinationIndex].isOccupied = 1;
    files[destinationIndex].isEncrypted = files[sourceIndex].isEncrypted; 

    files[sourceIndex].isOccupied = 0;
    memset(files[sourceIndex].name, 0, sizeof(files[sourceIndex].name));
    memset(files[sourceIndex].content, 0, sizeof(files[sourceIndex].content));
    files[sourceIndex].size = 0;

    printf("File '%s' moved to '%s'.\n", source, destination);
}

void compressFile(const char *filename) 
{
    int fileIndex = -1;

    for (int i = 0; i < MAX_FILES; ++i) {
        if (files[i].isOccupied == 1 && strcmp(files[i].name, filename) == 0) {
            fileIndex = i;
            break;
        }
    }

    if (fileIndex == -1) {
        printf("File '%s' not found. Cannot compress.\n", filename);
        return;
    }

    if (files[fileIndex].isEncrypted) {
        printf("File '%s' is encrypted. Cannot compress encrypted file.\n", filename);
        return;
    }

    char compressedContent[MAX_FILE_CONTENT];
    int compressedIndex = 0;

    int length = strlen(files[fileIndex].content);
    for (int i = 0; i < length; ++i) {
        int count = 1;
        while (i < length - 1 && files[fileIndex].content[i] == files[fileIndex].content[i + 1]) {
            count++;
            i++;
        }
        compressedContent[compressedIndex++] = files[fileIndex].content[i];
        compressedContent[compressedIndex++] = count + '0'; 
    }
    compressedContent[compressedIndex] = '\0'; 

    strcpy(files[fileIndex].content, compressedContent);
    files[fileIndex].size = strlen(compressedContent);

    printf("File '%s' compressed using Run-Length Encoding (RLE).\n", filename);
}

void decompressFile(const char *filename) 
{
    int fileIndex = -1;


    for (int i = 0; i < MAX_FILES; ++i) {
        if (files[i].isOccupied == 1 && strcmp(files[i].name, filename) == 0) {
            fileIndex = i;
            break;
        }
    }

    if (fileIndex == -1) {
        printf("File '%s' not found. Cannot decompress.\n", filename);
        return;
    }

    if (files[fileIndex].isEncrypted) {
        printf("File '%s' is encrypted. Cannot decompress encrypted file.\n", filename);
        return;
    }

    char decompressedContent[MAX_FILE_CONTENT]; 
    int decompressedIndex = 0;


    int length = strlen(files[fileIndex].content);
    for (int i = 0; i < length; i += 2) {
        char character = files[fileIndex].content[i];
        int count = files[fileIndex].content[i + 1] - '0'; 

        for (int j = 0; j < count; ++j) {
            decompressedContent[decompressedIndex++] = character;
        }
    }
    decompressedContent[decompressedIndex] = '\0'; 

    strcpy(files[fileIndex].content, decompressedContent);
    files[fileIndex].size = strlen(decompressedContent);

    printf("File '%s' decompressed using Run-Length Encoding (RLE).\n", filename);
}

void listFiles() 
{
    printf("List of files:\n");
    for (int i = 0; i < MAX_FILES; ++i) {
        if (files[i].isOccupied) {
            printf("%s\n", files[i].name);
        }
    }
}

void showSize(const char *filename) 
{
    int fileIndex = -1;

    for (int i = 0; i < MAX_FILES; ++i) {
        if (files[i].isOccupied == 1 && strcmp(files[i].name, filename) == 0) {
            fileIndex = i;
            break;
        }
    }

    if (fileIndex == -1) {
        printf("File '%s' not found. Cannot show size.\n", filename);
        return;
    }

    printf("Size of file '%s': %d bytes\n", filename, files[fileIndex].size);
}

void loadFileSystem() 
{
    FILE *file = fopen("filesystem_data.txt", "r");
    if (file == NULL) {
        printf("Directory created.\n");
        return;
    }

    fread(files, sizeof(struct File), MAX_FILES, file);
    fclose(file);
}

void saveFileSystem() 
{
    FILE *file = fopen("filesystem_data.txt", "w");
    if (file == NULL) {
        printf("Error saving filesystem data.\n");
        return;
    }

    fwrite(files, sizeof(struct File), MAX_FILES, file);
    fclose(file);
}

void delDir() 
{
    char filename[] = "filesystem_data.txt";
    if (remove(filename) == 0) 
    {
        printf("Directory deleted.\n");
    } else 
    {
        printf("Error deleting directory");
    }
}

int main(int argc, char *argv[]) 
{
    initializeFileSystem();
    loadFileSystem();
    if (argc < 1) {
        printf("Correct Syntax: <command> [arguments]\n");
        return 1;
    }

    if (strcmp(argv[1], "list") == 0) {
        if (argc != 2) {
            printf("Correct Syntax: list\n");
            return 1;
        }
        listFiles();
    } else if (strcmp(argv[1], "delDir") == 0) {
        if (argc != 2) {
            printf("Correct Syntax: delDir\n");
            return 1;
        }
        delDir();
        return 0;
    } else if (strcmp(argv[1], "create") == 0) {
        if (argc != 3) {
            printf("Correct Syntax: create <filename>\n");
            return 1;
        }
        createFile(argv[2]);
    } else if (strcmp(argv[1], "delete") == 0) {
        if (argc != 3) {
            printf("Correct Syntax: delete <filename>\n");
            return 1;
        }
        deleteFile(argv[2]);
    } else if (strcmp(argv[1], "read") == 0) {
        if (argc != 3) {
            printf("Correct Syntax: read <filename>\n");
            return 1;
        }
        readFile(argv[2]);
    } else if (strcmp(argv[1], "write") == 0) {
        if (argc != 4) {
            printf("Correct Syntax: write <filename> <content>\n");
            return 1;
        }
        writeFile(argv[2], argv[3]);
    } else if (strcmp(argv[1], "encrypt") == 0) {
        if (argc != 4) {
            printf("Correct Syntax: encrypt <filename> <password>\n");
            return 1;
        }
        encryptAES(argv[2], argv[3]);
    } else if (strcmp(argv[1], "decrypt") == 0) {
        if (argc != 4) {
            printf("Correct Syntax: decrypt <filename> <password>\n");
            return 1;
        }
        decryptAES(argv[2], argv[3]);
    } else if (strcmp(argv[1], "copy") == 0) {
        if (argc != 4) {
            printf("Correct Syntax: copy <source> <destination>\n");
            return 1;
        }
        copyFile(argv[2], argv[3]);
    } else if (strcmp(argv[1], "move") == 0) {
        if (argc != 4) {
            printf("Correct Syntax: move <source> <destination>\n");
            return 1;
        }
        moveFile(argv[2], argv[3]);
    } else if (strcmp(argv[1], "compress") == 0) {
        if (argc != 3) {
            printf("Correct Syntax: compress <filename>\n");
            return 1;
        }
        compressFile(argv[2]);
    } else if (strcmp(argv[1], "decompress") == 0) {
        if (argc != 3) {
            printf("Correct Syntax: decompress <filename>\n");
            return 1;
        }
        decompressFile(argv[2]);
    } else if (strcmp(argv[1], "showsize") == 0) {
        if (argc != 3) {
            printf("Correct Syntax: showsize <filename>\n");
            return 1;
        }
        showSize(argv[2]);
    } else {
        printf("Invalid command\n");
        return 1;
    }
    saveFileSystem();
    return 0;
}
