#include <stdio.h>
#include <string.h>

#include "timefmt.h"

enum { ADD, SUB };

int main(int argc, char *argv[])
{
    int seconds, operator, operand, i;
    char result[16];

    if (argc < 4) {
        printf("usage: %s [operator] [param1] ... [param_n]\n", argv[0]);
        return -1;
    }

    if (strcmp(argv[1], "add") == 0) {
        operator = ADD;
    } else if (strcmp(argv[1], "sub") == 0) {
        operator = SUB;
    } else {
        printf("unknown operator '%s'\n", argv[1]);
        return -1;
    }

    seconds = 0;
    for (i = 2; i < argc; i++) {
        operand = time_str_to_seconds(argv[i]);
        if (operand == -1) {
            printf("illegal parameter '%s'\n", argv[i]);
            return -1;
        }
        if (i == 2) {
            seconds = operand;
        } else if (operator == ADD) {
            seconds += operand;
        } else if (operator == SUB) {
            seconds -= operand;
        }
    }
    seconds_to_time_str(seconds, result, sizeof(result));
    if (strcmp(result, "") == 0) {
        printf("calculation failed\n");
        return -2;
    }

    printf("%s\n", result);

    return 0;
}
