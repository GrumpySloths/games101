CC = g++
# CFLAGS = -Wall -g
CFLAGS =  


test: test.cpp
	$(CC) $(CFLAGS)  $< -o $@ &&./$@

test2.o: test2.c
	$(CC) $(CFLAGS)  $< -o $@ &&./$@

test3: test3.c
	$(CC) $(CFLAGS)  $< -o $@ &&./$@

hash.o:hash.c
	$(CC) $(CFLAGS)  $< -o $@ &&./$@
	
clean:
	rm -f *.o executable
