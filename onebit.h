#ifndef ONEBIT_H
#define ONEBIT_H

#include <stdint.h>

void init_onebit();
int predict_onebit(uint64_t addr);
void update_onebit(uint64_t addr, int taken);

#endif