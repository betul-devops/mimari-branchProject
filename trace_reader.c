#include <stdio.h>
int read_trace(FILE *file, char *address, char *outcome) {
    char temp;
    int res = fscanf(file, "%s  %c", address, &temp);
    *outcome = temp;
    return res;
}
