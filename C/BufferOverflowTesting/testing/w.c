#include <fcntl.h>
#include <unistd.h>

int main(){
    char *path = "./tempfile";
    /* Open a file. */
    int fd;
    fd = open(path, O_WRONLY);

    char buff[8] = {0};
    read(fd, buff, 7);

    return 0;
}
