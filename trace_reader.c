#include <stdio.h>
#include <string.h>


/**
 * Valgrind/Lackey çıktısını ayrıştıran modül.
 * Proje teklifindeki 'Trace Parser Unit' görevini yürütür. 
 */

int read_trace(FILE *file, char *address, char *outcome) {
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char addr_tmp[128];
        char out_tmp;

        // Hem virgüllü (0x123,1) hem boşluklu (0x123 T) formatı dener
        if (sscanf(line, "%[^,],%c", addr_tmp, &out_tmp) == 2 || 
            sscanf(line, "%s %c", addr_tmp, &out_tmp) == 2) {
            
            strcpy(address, addr_tmp);
            // Eğer okunan değer rakamsa (0/1) harfe çevir
            if (out_tmp == '1' || out_tmp == 'T') *outcome = 'T';
            else *outcome = 'N';
            
            return 2;
        }
    }
    return 0;
}
