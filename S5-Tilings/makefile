CFLAGS = -Wall -Wextra -std=c99 -g

OBJS = queue.o board.o color.o tile.o player.o pattern_utils.o pattern.o set.o connection.o influence.o symetries.o loops.o adjacencies.o blocs.o

all: code

%.o: src/%.c src/%.h                                                                                
		gcc -c $(CFLAGS) $< -o $@

test: $(OBJS) tst/test.c
		gcc $(CFLAGS) $(OBJS) tst/test.c -o test.o && ./test.o

clean:
		rm -f *.o project.exe

code: $(OBJS) src/project.c
		gcc $(CFLAGS) $(OBJS) src/project.c -o project

doc:
		doxygen Doxyfile
