#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "timefmt.h"

void fail(const char *);

int main(int argc, char *argv[])
{
    int seconds = 0;
    int printed = 0;
    int i = 0;
    char *timestr;
    size_t size = 64;

    if (argc < 2) {
        fail(argv[0]);
    }

    seconds =  time_str_to_seconds(argv[1]);
    if (seconds == -1) {
        fail(argv[0]);
    }

    while (seconds > 0) {
        timestr = (char *)malloc(sizeof(char) * size);
        seconds_to_time_str(seconds, timestr, size);
        printed = printf("%s ", timestr);
        fflush(stdout);
        sleep(1);
        seconds--;
        for (i = 0; i < printed; i++) {
            putchar('\b');
        }
        fflush(stdout);
        free(timestr);
    }

    return 0;
}

void fail(const char *arg0)
{
    printf("usage: %s time, with time formatted as 1h15m30s\n", arg0);
    exit(1);
}
