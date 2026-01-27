CFLAGS = -g -std=gnu11 -Werror -Wall -Wextra -Wpedantic -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition
LDFLAGS = -lm -pthread

mdu: file_disc_space.o queue.o mdu.o info.o thread.o
	gcc $(LDFLAGS) -o mdu file_disc_space.o queue.o info.o thread.o mdu.o

file_disc_space.o: file_disc_space.c file_disc_space.h queue.h
	gcc $(CFLAGS) -c file_disc_space.c -o file_disc_space.o

queue.o: queue.c queue.h
	gcc $(CFLAGS) -c queue.c -o queue.o

mdu.o: mdu.c file_disc_space.h queue.h
	gcc $(CFLAGS) -c mdu.c -o mdu.o

info.o: info.c info.h queue.h
	gcc $(CFLAGS) -c info.c -o info.o

thread.o: thread.c thread.h info.h
	gcc $(CFLAGS) -c thread.c -o thread.o

clean:
	rm -f *.o mdu