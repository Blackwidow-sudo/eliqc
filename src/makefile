PROGNAME = licalc

CC = gcc
CFLAGS = -Wall -Werror -Wextra

# $@ refers to the target (licalc)
# $^ refers to the target's dependencies (main.o functions.o)
$(PROGNAME): main.o functions.o
	$(CC) $(CFLAGS) $^ -o ../bin/$@ -lcs50

main.o: main.c
	$(CC) $(CFLAGS) -c $^

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o *.gch