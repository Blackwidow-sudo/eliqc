PROGNAME = eliqc

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
OBJS=obj/main.o obj/functions.o
BIN=bin/eliqc
SUBMITNAME=eliqc.zip

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) -lcs50

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) obj/*.o *.gch

submit:
	$(RM) $(SUBMITNAME)
	zip $(SUBMITNAME) $(BIN)


# old stuff
# $@ refers to the target (licalc)
# $^ refers to the target's dependencies (main.o functions.o)
#$(PROGNAME): main.o functions.o
#	$(CC) $(CFLAGS) $^ -o ../bin/$@ -lcs50

#main.o: main.c
#	$(CC) $(CFLAGS) -c $^

#functions.o: functions.c functions.h
#	$(CC) $(CFLAGS) -c $^