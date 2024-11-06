CC = g++ -std=c++11 -g
CFLAGS = -c -Wall
LFLAGS = -Wall
exe = main

all: $(exe)

game.o: game.cpp game.h room.h event.h wumpus.h bats.h stalactites.h gold.h passage.h
	$(CC) $(CFLAGS) game.cpp

adventurer.o: adventurer.cpp adventurer.h
	$(CC) $(CFLAGS) adventurer.cpp

room.o: room.cpp room.h adventurer.h event.h wumpus.h bats.h stalactites.h gold.h passage.h
	$(CC) $(CFLAGS) room.cpp

event.o: event.cpp event.h
	$(CC) $(CFLAGS) event.cpp

wumpus.o: wumpus.cpp wumpus.h event.h
	$(CC) $(CFLAGS) wumpus.cpp

bats.o: bats.cpp bats.h event.h
	$(CC) $(CFLAGS) bats.cpp

stalactites.o: stalactites.cpp stalactites.h event.h
	$(CC) $(CFLAGS) stalactites.cpp

gold.o: gold.cpp gold.h event.h
	$(CC) $(CFLAGS) gold.cpp

passage.o: passage.cpp passage.h event.h
	$(CC) $(CFLAGS) passage.cpp

main.o: main.cpp game.h adventurer.h room.h event.h wumpus.h bats.h stalactites.h
	$(CC) $(CFLAGS) main.cpp

main: game.o adventurer.o room.o event.o wumpus.o bats.o stalactites.o gold.o passage.o main.o
	$(CC) $(LFLAGS) game.o adventurer.o room.o event.o wumpus.o bats.o stalactites.o gold.o passage.o main.o -o $(exe)

clean:
	rm -rf *.o $(exe)