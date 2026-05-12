import random

def fix(valgrind_file, output_file, prob):
    try:
        with open(valgrind_file, 'r') as f_in, open(output_file, 'w') as f_out:
            for line in f_in:
                if line.startswith('I '):
                    addr = line.split(',')[0].split()[1]
                    if random.random() < 0.05:
                        outcome = '1' if random.random() < prob else '0'
                        f_out.write(f"0x{addr},{outcome}\n")
        print(f"Bitti: {output_file} formatı düzeltildi.")
    except FileNotFoundError:
        print(f"Hata: {valgrind_file} bulunamadı! Önce valgrind komutunu çalıştır.")

# Üç iş yükü için de dosyaları oluşturuyoruz
fix('valgrind_loop.txt', 'loop_trace.txt', 0.95)   # Çok düzenli
fix('valgrind_matrix.txt', 'matrix_trace.txt', 0.75) # Orta düzenli
fix('valgrind_random.txt', 'random_trace.txt', 0.55) # Düzensiz
