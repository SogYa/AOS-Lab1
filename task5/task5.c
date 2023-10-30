#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

extern int errno;
int get_type_of_permission(char *perrmission_type)
{
    int r = strstr(perrmission_type, "r") > 0;
    int w = strstr(perrmission_type, "w") > 0;

    if (r && w)
    {
        return O_RDWR;
    }
    else if (r)
    {
        return O_RDONLY;
    }
    else if (w)
    {
        return O_WRONLY;
    }
    else
    {
        return -1;
    }
}
void load_file(int file, int position, int user_action)
{
    int number_of_butes = 256;
    int seek_type;
    switch (user_action)
    {
    case 1:
        seek_type = SEEK_SET;
        break;
    case 2:
        seek_type = SEEK_CUR;
        break;
    case 3:
        seek_type = SEEK_END;
        break;
    default:
        seek_type = SEEK_SET;
    }
    lseek(file, position, seek_type);

    int n = 256;
    char *buf = calloc(n, sizeof(char));

    int info = read(file, buf, n);
    printf("read: %d error %d %s\n", info, errno, strerror(errno));
    printf("%s\n", buf);
    printf("(read %d bytes)\n", n);
    free(buf);
}

void write_file(int file)
{
    char *message = "Hello world";
    int info = write(file, message, strlen(message));
    printf("write: %d error %d %s\n", info, errno, strerror(errno));
}

int main(int argc, char *argv[])
{
    int user_action, file_position;
    if (argc != 3)
    {
        fprintf(stderr, "Больше 3 типов доступа: %s file [r|w]+\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
    int permission_type = get_type_of_permission(argv[2]);

    int file = open(filename, O_CREAT | permission_type, 0777);
    printf("open: %d error %d %s\n", file, errno, strerror(errno));
    write_file(file);

    printf("Введите позицию: ");
    scanf("%d", &file_position);

    printf("Введите тип позиционирования:\n1 - SEEK_SET\n2 - SEEK_CUR\n3 - SEEK_END\nТип позиционирования: ");
    scanf("%d", &user_action);

    load_file(file, file_position, user_action);
    close(file);
}
