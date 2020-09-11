#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "timefmt.h"

int time_str_to_seconds(const char *time_str)
{
    int i, n, acc, seconds;
    char c;

    seconds = 0;
    acc = 0;
    n = strlen(time_str);

    for (i = 0; i < n; i++) {
        c = time_str[i];
        if (isdigit(c)) {
            acc = acc * 10 + c - '0';
        }
        if (isalpha(c)) {
            switch (c) {
                case 'h':
                    seconds += acc * 3600;
                    acc = 0;
                    break;
                case 'm':
                    seconds += acc * 60;
                    acc = 0;
                    break;
                case 's':
                    seconds += acc;
                    acc = 0;
                    break;
                default:
                    return -1;
            }
        }
    }

    return seconds;
}

void seconds_to_time_str(int seconds, char *buf, size_t size)
{
    int hours, minutes;

    if (seconds <= 0) {
        snprintf(buf, size, "");
        return;
    }

    hours = 0;
    minutes = 0;

    if (seconds >= 3600) {
        hours = seconds / 3600;
        seconds -= hours * 3600;
    }
    if (seconds >= 60) {
        minutes = seconds / 60;
        seconds -= minutes * 60;
    }

    if (hours > 0) {
        snprintf(buf, size, "%dh%dm%ds", hours, minutes, seconds);
    } else if (minutes > 0) {
        snprintf(buf, size, "%dm%ds", minutes, seconds);
    } else if (seconds > 0) {
        snprintf(buf, size, "%ds", seconds);
    }
}
