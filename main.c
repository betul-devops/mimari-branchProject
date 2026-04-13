#include <stdio.h>

int read_trace(FILE *file, char *address, char *outcome);

void init_bimodal();
int get_index(char *address);
char predict_bimodal(int state);
void update_bimodal(int idx, char outcome);

void update_stats(char prediction, char outcome);
void print_stats();

extern int table[];

int main() {
    FILE *file = fopen("trace.txt", "r");
printf("LOOP WORKS\n");
    if (file == NULL) {
        printf("trace.txt yok!\n");
        return 1;
    }

    char address[20];
    char outcome;
    char prediction;   // ⭐ BURASI ÇOK ÖNEMLİ

    init_bimodal();

    while (read_trace(file, address, &outcome) == 2) {

        int idx = get_index(address);
        printf("DEBUG: idx=%d, tablodan_okunan=%d\n", idx, table[idx]); // Bunu ekle

        prediction = predict_bimodal(table[idx]);

        update_stats(prediction, outcome);

        update_bimodal(idx, outcome);
        printf("outcome='%c' ascii=%d\n", outcome, outcome);
    }

    print_stats();
    fclose(file);

    return 0;
}
