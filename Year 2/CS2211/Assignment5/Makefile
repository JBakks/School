CC = gcc
CFLAGS=-Wall -Wpedantic -Wextra -std=c99

sport: sport_db.o sport_events.o sport_athlete.o sport_registration.o readline.o
		gcc -o sport sport_db.o sport_events.o sport_athlete.o sport_registration.o readline.o


clean:
		rm -f *.o sport_db sport_events sport_athlete sport_registration readline