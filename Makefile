CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -I./include

OBJS = main.o file_io.o list_manager.o logic.o ui.o

all: enterprise

enterprise: $(OBJS)
	$(CC) $(CFLAGS) -o enterprise $(OBJS)

main.o:	src/main.c include/*.h
	$(CC) $(CFLAGS) -c src/main.c -o main.o
logic.o: src/logic.c include/*.h
	$(CC) $(CFLAGS) -c src/logic.c -o logic.o
ui.o: src/ui.c include/*.h
	$(CC) $(CFLAGS) -c src/ui.c -o ui.o
file_io.o: src/file_io.c include/*.h
	$(CC) $(CFLAGS) -c src/file_io.c -o file_io.o
list_manager.o: src/list_manager.c include/*.h
	$(CC) $(CFLAGS) -c src/list_manager.c -o list_manager.o

run: all
	./enterprise

clean:
	rm -f *.o enterprise