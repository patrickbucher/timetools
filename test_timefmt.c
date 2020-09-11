#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "timefmt.h"

typedef struct {
    char *time_str;
    int seconds;
} test_case;

static const test_case table[] = {
    {"", 0},
    {"1s", 1},
    {"30s", 30},
    {"1m", 60},
    {"1m59s", 119},
    {"1h15m59s", 4559},
    {"1h0m59s", 3659},
};

static void test_time_str_to_seconds()
{
    for (int i = 0; i < sizeof(table)/sizeof(table[0]); i++) {
        const char *input = table[i].time_str;
        const int expected = table[i].seconds;
        const int actual = time_str_to_seconds(input);
        if (actual != expected) {
            printf("time_str_to_seconds(%s): expected %d, got %d\n",
                    input, expected, actual);
            exit(1);
        }
    }
}

static void test_seconds_to_time_str()
{
    char *actual;
    size_t size = 10;

    for (int i = 0; i < sizeof(table)/sizeof(table[0]); i++) {
        const int input = table[i].seconds;
        const char *expected = table[i].time_str;
        actual = (char *)malloc(sizeof(char) * size);
        seconds_to_time_str(input, actual, size);
        const long unsigned int n = strlen(expected);
        if (strncmp(expected, actual, n) != 0) {
            printf("seconds_to_time_str(%d): expected %s, got %s\n",
                    input, expected, actual);
            free(actual);
            exit(1);
        }
        free(actual);
    }
}

int main()
{
    test_time_str_to_seconds();
    puts("test_time_str_to_seconds: ok");

    test_seconds_to_time_str();
    puts("test_seconds_to_time_str: ok");
}
