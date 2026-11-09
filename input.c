#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

int readLine(const char *prompt, char *buf, int size) {
    for (;;) {
        printf("%s", prompt);
        fflush(stdout);

        if (fgets(buf, size, stdin) == NULL) {
            return 0;                         /* input closed */
        }

        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';              /* normal case: strip newline */
        } else {
            int c;                            /* line was too long: throw away the rest */
            while ((c = getchar()) != '\n' && c != EOF) { }
        }

        if (buf[0] != '\0') {
            return 1;
        }
        printf("This cannot be empty.\n");
    }
}

int readInt(const char *prompt, int min, int max, int *out) {
    char line[32];

    for (;;) {
        if (!readLine(prompt, line, (int)sizeof line)) {
            return 0;
        }

        char *end;
        long value = strtol(line, &end, 10);
        while (*end == ' ' || *end == '\t') end++;   /* allow trailing spaces */

        if (end == line || *end != '\0' || value < min || value > max) {
            printf("Please enter a whole number from %d to %d.\n", min, max);
            continue;
        }

        *out = (int)value;
        return 1;
    }
}
