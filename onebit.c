#include <stdint.h>

#define TABLE_SIZE 1024

// 1-bit table
static uint8_t bht[TABLE_SIZE];

// initialize predictor
void init_onebit() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        bht[i] = 1; // default TAKEN
    }
}

// index calculation
static int get_index(uint64_t addr) {
    return addr % TABLE_SIZE;
}

// prediction
int predict_onebit(uint64_t addr) {
    int idx = get_index(addr);

    return bht[idx];
}

// update predictor
void update_onebit(uint64_t addr, int taken) {
    int idx = get_index(addr);

    bht[idx] = taken;
}