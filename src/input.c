#include <stdio.h>
#include <string.h>
#include "input.h"

static void clearRemainingInput() {
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

void readLineInput(const char *prompt, char *buffer, int size) {
    while (1) {
        int length;

        printf("%s", prompt);

        if (fgets(buffer, size, stdin) == NULL) {
            buffer[0] = '\0';
            return;
        }

        length = (int) strlen(buffer);

        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        } else {
            clearRemainingInput();
        }

        if (buffer[0] == '\0') {
            printf("Invalid input. Try again.\n");
        } else {
            return;
        }
    }
}

int readIntInput(const char *prompt) {
    char line[100];
    int value;
    char extra;

    while (1) {
        readLineInput(prompt, line, sizeof(line));

        if (sscanf(line, "%d %c", &value, &extra) == 1) {
            return value;
        }

        printf("Invalid input. Try again.\n");
    }
}

float readFloatInput(const char *prompt) {
    char line[100];
    float value;
    char extra;

    while (1) {
        readLineInput(prompt, line, sizeof(line));

        if (sscanf(line, "%f %c", &value, &extra) == 1) {
            return value;
        }

        printf("Invalid input. Try again.\n");
    }
}
