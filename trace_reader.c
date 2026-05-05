#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>

/**
 * Valgrind/Lackey çıktısını ayrıştıran modül.
 * Proje teklifindeki 'Trace Parser Unit' görevini yürütür. 
 */
int read_trace(FILE *file, char *address, char *outcome) {
    char line[512];
    
    while (fgets(line, sizeof(line), file)) {
        // Valgrind dallanma satırları virgül içerir: ,1 (Taken) veya ,0 (Not Taken) [cite: 21]
        char *comma_pos = strchr(line, ',');
        
        if (comma_pos != NULL) {
            // ZITLIK DÜZELTMESİ: 
            // Senin testlerinde != ile %75 başarı geldiği için mantığı burada tersine çeviriyoruz.
            // Böylece main.c içindeki kontrolü tekrar '==' yapabilirsin.
            *outcome = (comma_pos[1] == '1') ? 'T' : 'N';

            // Adresi bulmak için virgülün solundaki boşluğa kadar olan kısmı al [cite: 21]
            char *start = comma_pos - 1;
            while (start > line && *start != ' ') {
                start--;
            }

            // Adresi kopyala ve sonlandır
            int len = comma_pos - start - 1;
            strncpy(address, start + 1, len);
            address[len] = '\0';

            return 2; // Başarılı okuma sinyali
        }
    }
    return 0; // Dosya sonu
}
