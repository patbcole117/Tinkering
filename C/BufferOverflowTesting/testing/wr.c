#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void){
    int fd;
    char *path = "./tempfile";
    char fbuff[256];
    char ibuff[256];
    /* Open a file. */
    fd = open(path, O_WRONLY | O_CREAT, 0777);
    if(fd < 0){
        perror("open");
        exit(1);
    }
    /* Write to file. */
    memset(ibuff, 0, sizeof(ibuff));
    printf("Enter%d: ", (int)sizeof(ibuff));
    scanf("%255s", ibuff);
    write(fd, ibuff, 255);
    close(fd);

    /* Read from file. */

    fd = open(path, O_RDONLY);
    memset(fbuff, 0, sizeof(fbuff));
    read(fd, fbuff, 255);
    printf("%s\n", fbuff);
    
    return 0;
}
