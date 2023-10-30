#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

extern int errno;

int copy(int src_fd, int dst_fd, int n_bytes)
{
    int result = -1;
    void *src_buf = (void *)calloc(n_bytes, sizeof(char));
    int read_result = read(src_fd, src_buf, n_bytes);
    if (read_result >= 0)
        result = write(dst_fd, src_buf, n_bytes);
    free(src_buf);
    return result;
}

int main(int argc, char *argv[])
{
    int input_file, output_file, number_of_bytes;

    if (argc != 3)
    {
        const char *input_filename;
        const char *ouput_filename;
        printf("Введите имя входного файла и результирующего: ");
        scanf("%s %s", &input_filename, &ouput_filename);
        input_file = open(input_filename, O_RDONLY);
        printf("read: %d error %d %s\n", input_file, errno, strerror(errno));

        struct stat src_stat = {0};
        stat(input_filename, &src_stat);
        number_of_bytes = src_stat.st_size;
        output_file = open(ouput_filename, O_CREAT | O_RDWR, src_stat.st_mode);
    }
    else
    {
        const char *input_filename = argv[1];
        const char *output_filename = argv[2];
        input_file = open(input_filename, O_RDWR);
        struct stat src_stat = {0};
        stat(input_filename, &src_stat);
        output_file = open(output_filename, O_CREAT | O_RDWR, src_stat.st_mode);
        number_of_bytes = src_stat.st_size;
    }
    printf("read: %d error %d %s\n", input_file, errno, strerror(errno));

    printf("read: %d error %d %s\n", output_file, errno, strerror(errno));

    copy(input_file, output_file, number_of_bytes);
    if (argc == 3)
    {
        close(input_file);
        close(output_file);
    }
    return 0;
}