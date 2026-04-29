#include <stdlib.h>  // <--- BU EKSİK!
#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 1024 // 2^10 gibi düşün

int table[1024];

// init
void init_bimodal() {
    for (int i = 0; i < 1024; i++) {
        table[i] = 2; 
    }
}
int get_index(char *address) {
    // strtol yerine unsigned long kullanmak x86-64 adresleri için daha güvenlidir [cite: 39]
    unsigned long addr = strtoul(address, NULL, 16); 
    // 2 bit sağa kaydırarak çakışmaları azaltıyoruz 
    return (addr >> 2) % TABLE_SIZE;
}

// prediction
char predict_bimodal(int state) {
    // state: 0-1 NT, 2-3 T gibi düşün
    return (state >= 2) ? 'T' : 'N';
}

void update_bimodal(int idx, char outcome) {
    // Eğer sonuç Taken ('T') ise state'i artır
    if (outcome == 'T' || outcome == 84) {
        if (table[idx] < 3) {
            table[idx]++;
        }
    } 
    // Eğer sonuç Not Taken ('N') ise state'i azalt
    else if (outcome == 'N' || outcome == 78) {
        if (table[idx] > 0) {
            table[idx]--;
        }
    }
}
