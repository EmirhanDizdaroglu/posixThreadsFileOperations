    #include <stdio.h>
    #include <stdlib.h>
    #include <pthread.h>
    #include <string.h>

    typedef struct {
        char *fileName;
        int numberOfCharacters;
        int numberOfBytes;
        char *str;
    } THREAD;

    void *read_file(void *arg) {
        THREAD *thread_data = (THREAD*) arg;

        char *filename = thread_data->fileName;
        int num_chars = thread_data->numberOfCharacters;

        FILE *fp = fopen(filename, "r");
        if (!fp) {
            perror("ERROR It can not open!");
            pthread_exit(NULL);
        }

        char *buffer = (char *) malloc(num_chars + 1);
        if (!buffer) {
            perror("ERROR!");
            fclose(fp);
            pthread_exit(NULL);
        }

        memset(buffer, 0, num_chars + 1); // Tampon belleği sıfırlar ve 0 karakterleri ile doldurur

        int numberOfRead = fread(buffer, sizeof(char), num_chars, fp);//num_chars bayt büyüklüğündeki veriyi buffer belleğine okur
        //fread bellek bloğuna kopyalama yapabilmesi için boş bir buffera ihtiyaç duyarAncak veriyi saklamak
        // veya işlem yapmak için bir bellek bloğuna ihtiyaç duyduğunuzda buffer kullanmanız gerekebilir.
        buffer[numberOfRead] = '\0';

        printf("%s\n", buffer);

        fclose(fp);
        free(buffer);
        pthread_exit(NULL);
        return 0;
    }

    void *write_file(void *arg) {
        THREAD *thread_data = (THREAD*) arg;

        char *filename = thread_data->fileName;
        int num_bytes = thread_data->numberOfBytes;
        char *text = thread_data->str;

        FILE *fp = fopen(filename, "w");
        if (fp == NULL) {
            fprintf(stderr, "Error: could not open file %s\n", filename);
            pthread_exit(NULL);
        }

        size_t written_bytes = fwrite(text, sizeof(char), num_bytes, fp);

        if (written_bytes != (size_t) num_bytes) {
            fprintf(stderr, "Error: could not write to file %s\n", filename);
        }

        fclose(fp);
        pthread_exit(NULL);
        return 0;
    }

    void *open_file(void *arg) {
        char *filename = (char *) arg;
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
            fprintf(stderr, "Error: could not open file %s\n", filename);
            pthread_exit(NULL);
        }
        fclose(fp);
        pthread_exit(NULL);
        return 0;
    }

    void *close_file(void *arg) {
        char *filename = (char *) arg;

        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
            fprintf(stderr, "Error: could not open file %s\n", filename);
            pthread_exit(NULL);
        }
        fclose(fp);
        pthread_exit(NULL);
        return 0;
    }

    int main() {
        THREAD arguments = { NULL, 0, 0, NULL };// arguments değişkeni elemanları tanımlandı
        arguments.fileName = (char *) malloc(100 * sizeof(char));
        arguments.str = (char *) malloc(100 * sizeof(char));
        int option;
        pthread_t thread;

        do {
            printf("Choose an option:\n");
            printf("1. Read a file (name, character count) to the screen.\n");
            printf("2. (Name, Byte Count, Char String) Write to a file.\n");
            printf("3. Open a file (name)\n");
            printf("4. Close a file (name)\n");
            printf("0. Exit\n");
            printf("ENTER: ");
            scanf("%d", &option);

            // Read a file
            if (option == 1) {
                printf("Enter fileName and number of characters to read:\n");
                scanf("%s %d", arguments.fileName, &arguments.numberOfCharacters);
                pthread_create(&thread, NULL, read_file, (void *) &arguments);
                pthread_join(thread, NULL);
                continue;
            }
            // Write to a file
            if (option == 2) {
                printf("Enter fileName, number of bytes, and char str:\n");
                scanf("%s %d %s", arguments.fileName, &arguments.numberOfBytes, arguments.str);
                pthread_create(&thread, NULL, write_file, (void *) &arguments);
                pthread_join(thread, NULL);
                continue;
            }
            // Open a file
            if (option == 3) {
                printf("Enter fileName:\n");
                scanf("%s", arguments.fileName);
                pthread_create(&thread, NULL, open_file, (void *) &arguments);
                pthread_join(thread, NULL);
                continue;
            }
            // Close a file
            if (option == 4) {
                printf("Enter fileName:\n");
                scanf("%s", arguments.fileName);
                pthread_create(&thread, NULL, close_file, (void *) &arguments);
                pthread_join(thread, NULL);
                continue;
            }
            // Exit
            if (option == 0) {
                continue;
                // Invalid option
            } else {
                printf("Invalid selection. Please try once more.\n");
            }

        } while (option != 0);
        pthread_exit(0);
        return 0;
    }

