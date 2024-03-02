CC = gcc
CFLAGS = -fsanitize=address,undefined,leak -std=c99 -Og -Wall -g

triestest: triestest.o tries.o
	$(CC) -o $@ $^ $(CFLAGS)
triestest.o: triestest.c
	$(CC) -c $< $(CFLAGS)
tries.o: tries.c
	$(CC) -c $< $(CFLAGS)
clean: triestest
	rm *.o $<