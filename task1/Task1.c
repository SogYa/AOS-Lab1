#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    errno = 0;
    FILE *fp = fopen(argv[1], "r");

    perror("fopen() ");
    printf("errno: %d\n", errno);
	printf("strerror(%d): %s", errno, strerror(errno));
    
    return 0;
}