CC = gcc

CFLAGS = -Wall

TARGET = simulator

SRC = main.c bimodal.c onebit.c static_predictor.c trace_reader.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run_bimodal:
	./$(TARGET) trace.txt bimodal

run_onebit:
	./$(TARGET) trace.txt onebit

run_static_taken:
	./$(TARGET) trace.txt static_taken

run_static_not_taken:
	./$(TARGET) trace.txt static_not_taken