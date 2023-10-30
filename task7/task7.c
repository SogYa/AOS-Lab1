#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Ошибка: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    struct stat statbuffer = {0};
    stat(argv[1], &statbuffer);
    printf("Размер: %lu\n", statbuffer.st_size);
    printf("Номер устройства файла: %lu\n", statbuffer.st_dev);
    printf("i-узел файла inode: %lu\n", statbuffer.st_ino);
    printf("Тип файла: %u\n", statbuffer.st_mode);
    printf("Количество ссылок: %lu\n", statbuffer.st_nlink);
    printf("ID владельца: %u\n", statbuffer.st_uid);
    printf("ID группы: %u\n", statbuffer.st_gid);
    printf("ID устрйоства: %lu\n", statbuffer.st_rdev);
    printf("Размер блоков ввода вывода: %lu\n", statbuffer.st_blksize);
    printf("Количество выделенных/занятых блоков: %lu\n", statbuffer.st_blocks);
    printf("Время последнего доступа: %ld\n", statbuffer.st_atime);
    printf("Время последней модификации: %ld\n", statbuffer.st_mtime);
    printf("Время последнего изменения: %ld\n", statbuffer.st_ctime);

    return 0;
}