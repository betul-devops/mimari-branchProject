//predictorlar için zorulu, varying branch entropy

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    srand(time(NULL));

    int count = 0;

    for (int i = 0; i < 100000; i++) {

        int r = rand() % 2;

        if (r) {
            count++;
        }
        else {
            count--;
        }
    }

    printf("%d\n", count);

    return 0;
}