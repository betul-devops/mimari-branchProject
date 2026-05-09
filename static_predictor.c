#include "static_predictor.h"

// Always Taken Predictor
char predict_static_taken() {
    return 'T';
}

// Always Not Taken Predictor
char predict_static_not_taken() {
    return 'N';
}