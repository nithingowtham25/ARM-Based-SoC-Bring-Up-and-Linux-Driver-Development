#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    unsigned int result;
    int fd;
    int i, j;
    char input = 0;

    /* file descriptor */

    /* open device file for reading and writing */
    /* use 'open' to open '/dev/multiplier' */
    fd = open("/dev/multiplier", O_RDWR);

    /* handle error opening file */
    if (fd == -1){
        printf("Failed to open device file!\n");
        return -1;
    }

    while (input != 'q'){ /* continue unless user entered 'q' */

        for (i = 0; i <= 16; i++){
            for (j = 0; j <= 16; j++){

                /* write values to registers using char dev */
                /* use write to write i and j to peripheral */
                unsigned int write_buf[2];
                write_buf[0] = i;
                write_buf[1] = j;
                write(fd, write_buf, 2 * sizeof(unsigned int));

                /* read i, j, and result using char dev */
                /* use read to read from peripheral */
                unsigned int read_buf[3];
                read(fd, read_buf, 3 * sizeof(unsigned int));

                unsigned int read_i = read_buf[0];
                unsigned int read_j = read_buf[1];
                result = read_buf[2];

                /* print unsigned ints to screen */
                printf("%u * %u = %u ", read_i, read_j, result);

                /* validate result */
                if (result == (i * j))
                    printf("Result Correct!\n");
                else
                    printf("Result Incorrect!\n");
            }
        }

        /* read from terminal */
        printf("Press 'q' to quit or any key to continue...\n");
        input = getchar();
    }

    close(fd);
    return 0;
}