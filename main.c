#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "onebit.h"
#include "static_predictor.h"

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

typedef enum {
    BIMODAL,
    ONEBIT,
    STATIC_TAKEN,
    STATIC_NOT_TAKEN
} PredictorType;

void print_results(char *predictor_name,
                   double accuracy,
                   double miss_rate,
                   double cpi) {

    printf("\n");
    printf("==================================================\n");
    printf("Predictor              Accuracy      Miss Rate      CPI\n");
    printf("==================================================\n");

    printf("%-22s %-12.2f%% %-14.2f%% %.3f\n",
           predictor_name,
           accuracy,
           miss_rate,
           cpi);

    printf("==================================================\n");
}

void save_to_csv(char *workload_name,
                 char *predictor_name,
                 double accuracy,
                 double miss_rate,
                 double cpi) {

    FILE *csv = fopen("results.csv", "a");

    if (csv == NULL) {
        printf("CSV dosyasi acilamadi!\n");
        return;
    }

    fprintf(csv,
        "%s,%s,%.2f,%.2f,%.3f\n",
        workload_name,
        predictor_name,
        accuracy,
        miss_rate,
        cpi);

    fclose(csv);
}

int main(int argc, char *argv[]) {
    // Kullanım kontrolü
    if (argc < 3) {
        printf("Kullanim: %s <tracefile> <predictor>\n", argv[0]);
        printf("Predictor secenekleri: bimodal | onebit\n");
        return 1;
    }

    // Trace dosyasını aç
    FILE *file = fopen(argv[1], "r");


    if (file == NULL) {
        printf("Hata: Trace dosyasi acilamadi!\n");
        return 1;
    }

    char address[20];
    char outcome;
    char prediction;

    PredictorType predictor;
    char predictor_name[50];
    char workload_name[100];
    strcpy(workload_name, argv[1]);

    // CSV header oluştur
    FILE *check = fopen("results.csv", "r");
        if (check == NULL) {
            FILE *csv = fopen("results.csv", "w");
            if (csv != NULL) {
                fprintf(csv, "Workload,Predictor,Accuracy,MissRate,CPI\n");
                fclose(csv);
            }
        }
        else {
            fclose(check);
        }

    // Predictor seçimi
    if (strcmp(argv[2], "bimodal") == 0) {
        predictor = BIMODAL;
        strcpy(predictor_name, "Bimodal");
        init_bimodal();
    }

    else if (strcmp(argv[2], "onebit") == 0) {
        predictor = ONEBIT;
        strcpy(predictor_name, "OneBit");
        init_onebit();
    }

    else if (strcmp(argv[2], "static_taken") == 0) {
        predictor = STATIC_TAKEN;
        strcpy(predictor_name, "Static Taken");
    }

    else if (strcmp(argv[2], "static_not_taken") == 0) {
        predictor = STATIC_NOT_TAKEN;
        strcpy(predictor_name, "Static Not Taken");
    }

    else {
        printf("Bilinmeyen predictor tipi!\n");
        return 1;
    }

    printf("Simulasyon baslatildi...\n");

    // 2. Simülasyon Döngüsü
    while (read_trace(file, address, &outcome) == 2) {
        total_branches++;

        int idx = get_index(address);

        if (predictor == BIMODAL) {
            prediction = predict_bimodal(table[idx]);
            if (prediction == outcome) {
                correct_predictions++;
            }
            update_bimodal(idx, outcome);
        }

        else if (predictor == ONEBIT) {
            prediction = predict_onebit(strtoull(address, NULL, 16));

            if (prediction == (outcome == 'T')) {
                correct_predictions++;
            }
            update_onebit(strtoull(address, NULL, 16), outcome == 'T');
        }

        else if (predictor == STATIC_TAKEN) {
            prediction = predict_static_taken();

                if (prediction == outcome) {
                    correct_predictions++;
                }
        }

        else if (predictor == STATIC_NOT_TAKEN) {
            prediction = predict_static_not_taken();
                if (prediction == outcome) {
                    correct_predictions++;
                }
        }

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

        print_results(
            predictor_name,
            accuracy,
            misprediction_rate * 100,
            final_cpi
        );

        save_to_csv(
            workload_name,
            predictor_name,
            accuracy,
            misprediction_rate * 100,
            final_cpi
        );
    }

    fclose(file);
    return 0;
}
