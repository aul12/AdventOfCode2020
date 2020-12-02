#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define BUF_SIZE 4096

int main(void) {
    int fd = open("input", O_RDONLY);
    assert(fd > 0);

    char inputBuf[BUF_SIZE];

    int *numbers = NULL;
    size_t numOfNumbers = 0;

    int readed;
    int num = 0;
    do {
        readed = read(fd, inputBuf, BUF_SIZE);

        for (size_t i=0; i<readed; ++i) {
            char c = inputBuf[i];
            if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
            } else {
                numbers = realloc(numbers, (numOfNumbers + 1) * sizeof(int));
                assert(numbers);
                numbers[numOfNumbers] = num;
                numOfNumbers += 1;
                num = 0;
            }
        }
    } while (readed > 0);

    for (size_t x=0; x<numOfNumbers; ++x) {
        for (size_t y=x; y<numOfNumbers; ++y) {
            if (numbers[x] + numbers[y] == 2020) {
                printf("x=%d, y=%d: x*y=%d, x+y=%d\n", numbers[x], numbers[y],
                        numbers[x]*numbers[y], numbers[x] + numbers[y]);
            }
        }
    }

    for (size_t x=0; x<numOfNumbers; ++x) {
        for (size_t y=x; y<numOfNumbers; ++y) {
            for (size_t z=y; z<numOfNumbers; ++z) {
                if (numbers[x] + numbers[y] + numbers[z]  == 2020) {
                    printf("x=%d, y=%d, z=%d: x*y=%d, x+y=%d\n", 
                            numbers[x], numbers[y], numbers[z],
                            numbers[x]*numbers[y]*numbers[z], numbers[x] + numbers[y]);
                }
            }
        }
    }
    free(numbers);
    close(fd);

    return 0;
}
