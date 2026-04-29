#include <stdio.h>
#include <string.h>

int read_trace(FILE *file, char *address, char *outcome) {
    char line[256];
    // Satır satır oku
    while (fgets(line, sizeof(line), file)) {
        // Valgrind dallanma satırları genelde " J " veya " C " ile başlar
        if (strstr(line, " J ") != NULL || strstr(line, " C ") != NULL) {
            char *comma = strchr(line, ',');
            if (comma != NULL) {
                // Virgülden önceki adres kısmını al (Örn: 00400501)
                // Satırdaki 'J' harfinden sonrasına odaklan
                sscanf(line, "%*s %[^,]", address);
                
                // Virgülden sonraki rakamı (1 veya 0) kontrol et
                int taken = (comma[1] == '1');
                *outcome = taken ? 'T' : 'N';
                return 2; 
            }
        }
    }
    return 0;
}
