#include <stdio.h>
#include <stdlib.h>

// Fonksiyon prototipleri
int read_trace(FILE *file, char *address, char *outcome);
void init_bimodal();
int get_index(char *address);
char predict_bimodal(int state);
void update_bimodal(int idx, char outcome);

// İstatistik değişkenleri
long total_branches = 0;
long correct_predictions = 0;
extern int table[];

int main() {
    // 1. Dosya Kontrolü
    FILE *file = fopen("trace.txt", "r");
    if (file == NULL) {
        printf("Hata: trace.txt dosyası bulunamadı!\n");
        printf("Lütfen Valgrind çıktısını trace.txt olarak kaydedin.\n");
        return 1;
    }

    char address[20];
    char outcome;
    char prediction;

    init_bimodal();
    printf("Simülasyon başlatıldı...\n");

    // 2. Simülasyon Döngüsü
    while (read_trace(file, address, &outcome) == 2) {
        total_branches++;

        int idx = get_index(address);
        prediction = predict_bimodal(table[idx]);

        // Doğruluk kontrolü
        if (prediction == outcome) {
            correct_predictions++;
        }

        // Tahminleyiciyi güncelle
        update_bimodal(idx, outcome);
    }

    // 3. Raporlama (Proposal'daki formüllere göre)
    if (total_branches > 0) {
        double accuracy = (double)correct_predictions / total_branches * 100;
        double misprediction_rate = 1.0 - ((double)correct_predictions / total_branches);
        
        // Raporunda belirttiğin CPI formülü: CPI = CPI_base + (MispredictionRate * Penalty)
        // x86-64 için tipik penaltı değerini 15 çevrim (cycle) varsayalım.
        double cpi_base = 1.0;
        int penalty = 15; 
        double final_cpi = cpi_base + (misprediction_rate * penalty);

        // Değişkenleri doğru yazdırmak için çift '%' işaretini tek yap
printf("Tahmin Doğruluğu (Acc)    : %.2f%%\n", accuracy); 
printf("Hata Oranı (Miss Rate)    : %.2f%%\n", misprediction_rate * 100);
printf("Hesaplanan Tahmini CPI    : %.3f\n", final_cpi);
    }

    fclose(file);
    return 0;
}
