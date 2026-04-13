#include <stdio.h>

int total = 0;
int correct = 0;

void update_stats(char prediction, char outcome) {
    total++;
    // YENİ DEBUG SATIRI (Bunu ekle):
    printf("KIYASLAMA: Pred ASCII=%d, Real ASCII=%d\n", (int)prediction, (int)outcome);
    
    if (prediction == outcome) {
        correct++;
    }
}

void print_stats() {
    printf("Total: %d\n", total);
    printf("Correct: %d\n", correct);
    printf("Accuracy: %.2f%%\n", (correct * 100.0) / total);
}
