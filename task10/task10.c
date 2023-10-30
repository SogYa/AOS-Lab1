#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    int file = open(filename, O_RDONLY);
    long file_size = lseek(file, 0, SEEK_END);
    if (file_size > 0)
    {
        do
        {
            char letter = '\0';
            read(file, &letter, 1);
            printf("%c", letter);
        } while (lseek(file, -2, SEEK_CUR) >= 0);
    }
    printf("\n");
    close(file);
    return 0;
}