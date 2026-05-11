//düzenli branch pattern,predictor için kolay workload

#include <stdio.h>

int main() {

    int sum = 0;

    for (int i = 0; i < 100000; i++) {

        if (i % 2 == 0) {
            sum += i;
        }
        else {
            sum -= i;
        }
    }

    printf("%d\n", sum);

    return 0;
}