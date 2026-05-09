#include <stdio.h>

// Raporunda belirttiğin "Always-Taken" stratejisi 
char predict_static_always_taken() {
    return 'T';
}

// Raporunda belirttiğin "Always-Not-Taken" stratejisi [cite: 44]
char predict_static_always_not_taken() {
    return 'N';
}
